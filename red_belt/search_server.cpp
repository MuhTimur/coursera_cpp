#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
	istringstream words_input(line);
	return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

SearchServer::SearchServer(istream& document_input) {
	UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	InvertedIndex new_index;

	for (string current_document; getline(document_input, current_document); ) {
		new_index.Add(move(current_document));
	}

	index = move(new_index);
}

void SearchServer::AddQueriesStream(
	istream& query_input, ostream& search_results_output
) {

	vector<pair<size_t, size_t>> search_results(50'000);

	for (string current_query; getline(query_input, current_query); ) {
		const auto words = SplitIntoWords(current_query);

		fill(search_results.begin(), search_results.end(), make_pair(0, 0));

		// make vector with pairs {doc_id , hitcount} for each word
		for (const auto& word : words) {
			for (const pair<size_t, size_t>& docid : index.Lookup(word)) {
				search_results[docid.first].first = docid.first;
				search_results[docid.first].second += docid.second;
			}
		}

		partial_sort(
			begin(search_results),
			// first 5 results
			search_results.size() < 5 ? end(search_results) : begin(search_results) + 5,
			end(search_results),
			[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
				int64_t lhs_docid = lhs.first;
				auto lhs_hit_count = lhs.second;
				int64_t rhs_docid = rhs.first;
				auto rhs_hit_count = rhs.second;
				return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
			}
		);

		// print only non-empty pairs
		search_results_output << current_query << ':';
		for (auto [docid, hitcount] : Head(search_results, 5)) {
			if(!(docid == 0 && hitcount == 0))
			    search_results_output << " {"
				    << "docid: " << docid << ", "
				    << "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	}
}

void InvertedIndex::Add(const string& document) {
	docs.push_back(document);

	const size_t docid = docs.size() - 1;
	auto words = SplitIntoWords(document);

	map<string, map<size_t, size_t>> tmp_map;

	// count the number of occurrences of a word in a document 
	for (const auto& word : words) {
		tmp_map[word][docid] = count(words.begin(), words.end(), word);
	}

	// make vector of pairs from map and move it to index
	for (const auto& word : tmp_map) {
		vector<pair<size_t, size_t>> tmp_vec(tmp_map[word.first].begin(), tmp_map[word.first].end());
		move(tmp_vec.begin(), tmp_vec.end(), inserter(index[word.first], index[word.first].end()));
	}
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string& word) const {
	// return vector of pairs {doc_id, hitcount}
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	}
	else {
		return {};
	}
}