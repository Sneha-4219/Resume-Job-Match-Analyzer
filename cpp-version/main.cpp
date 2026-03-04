/*
==========================================================
Resume – Job Match Analyzer (C++ | STL | OOP | Hashing)
Author: Sneha Sharma

Description:
CLI-based tool that analyzes resume and job description
text to compute a weighted skill match score.

Core Concepts Used:
- String normalization & tokenization
- Hashing (unordered_map, unordered_set)
- Frequency counting
- Weighted scoring with capped contribution
- Clean OOP separation of concerns

Time Complexity: O(n + m)
==========================================================
*/
#include  <bits/stdc++.h>
using namespace std;

class TextProcessor{
private:
    // Common filler words that should not be treated as skills
    unordered_set<string> stopWords;
public:
    // Initialize stopwords once when object is created 
    TextProcessor() {
        stopWords = {
            "and", "the", "for", "with", "a", "an",
            "to", "of", "in", "on", "at", "by",
            "is", "are", "looking", "i", "am"
        };
    }

    // Normalize text:
    // - Convert to lowercase
    // - Preserve '+' and '#'
    // - Replace other punctuation with spaces
    string normalize(const string &text) {
        string normalized = "";
        for(char ch : text) {
            if(isalpha(ch) || ch == '+' || ch == '#') {
                normalized.push_back(tolower(ch));
            } else if(ch == '.') {
                continue;
            }else {
                normalized.push_back(' ');
            }
        }
        return normalized;
    }

    // Split normalized string into individual words manually
    // (avoids using regex for full control)
    vector<string> tokenize(const string &text) {
        vector<string> words;
        string currentWord;

        for(char ch : text) {
            if(ch != ' '){
                currentWord += ch;
            } else {
                if(!(currentWord.empty())) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
        }
        if(!(currentWord.empty())){
            words.push_back(currentWord);
        }

        return words;
    }
    
    // Full preprocessing pipeline:
    // normalize → tokenize → remove stopwords
    vector<string> process(const string &text) {
        string cleaned = normalize(text);
        vector<string> tokens = tokenize(cleaned);

        vector<string> filtered;

        for(const string &word : tokens) {
            if(stopWords.find(word) == stopWords.end()) {
                filtered.push_back(word);
            }
        }

        return filtered;
    }

};

// Responsible for matching processed resume tokens
// against job description tokens using weighted scoring
class SkillMatcher {
private:
    unordered_map<string, int> resumeFreq;
    unordered_set<string> jobSet;

    vector<string> matchedSkills;
    vector<string> missingSkills;

    int totalPoints;

public:
    SkillMatcher() {
        totalPoints = 0;
    }

    void match(const vector<string> &resume, const vector<string> &job) {

        // Reset internal state before each new match
        resumeFreq.clear();
        jobSet.clear();
        matchedSkills.clear();
        missingSkills.clear();
        totalPoints = 0;

        // Build frequency map of resume skills
        // Key: skill | Value: frequency in resume
        for(const string &word : resume) {
            resumeFreq[word]++;
        }

        // Store unique job skills (duplicates removed)
        for(const string &word : job) {
            jobSet.insert(word);
        }

        // For each required job skill:
        // - If present in resume → add capped weighted points
        // - Else → mark as missing
        for(const string &skill : jobSet) {
            if(resumeFreq.count(skill)) {
                matchedSkills.push_back(skill);

                int freq = resumeFreq[skill];

                // Cap contribution at 3 to prevent score inflation
                totalPoints += min(freq, 3);
            } else {
                missingSkills.push_back(skill);
            }
        }
    }

    const vector<string>& getMatched() const {
        return matchedSkills;
    }
    
    const vector<string>& getMissing() const {
        return missingSkills;
    }

    int getTotalPoints() const{
        return totalPoints;
    }

    int getJobSkillCount() const {
        return jobSet.size();
    }
};

// Responsible only for computing final percentage score
// Keeps scoring logic independent from matching logic
class Scorer {
public:
    double calculateScore(int totalPoints, int jobCount) {
        // Weighted score formula:
        // (TotalPoints / (Cap × NumberOfJobSkills)) × 100
        double score = 0;
        if(jobCount > 0) {
            score = (double)totalPoints / (3 * jobCount) * 100;
        }
        return score;
    }
};

// Entry point: orchestrates preprocessing,
// matching, and scoring components
int main() {

    string resume;
    string job;

    cout << "Enter Resume:\n";
    getline(cin, resume);

    cout << "Enter Job Description:\n";
    getline(cin, job);
    
    TextProcessor tp;
    SkillMatcher sm;
    Scorer scorer;

    // Preprocess raw text into cleaned skill tokens
    vector<string> resumeProcessed = tp.process(resume);
    vector<string> jobProcessed = tp.process(job);

    // Perform weighted skill matching
    sm.match(resumeProcessed, jobProcessed);

    vector<string> matchedSkills = sm.getMatched();
    vector<string> missingSkills = sm.getMissing();

    int totalPoints = sm.getTotalPoints();
    int jobCount = sm.getJobSkillCount();

    // Calculate final percentage score
    double score = scorer.calculateScore(totalPoints, jobCount);

    // Sort output alphabetically for clean display
    sort(matchedSkills.begin(), matchedSkills.end());
    sort(missingSkills.begin(), missingSkills.end());

    cout << "\n====== Resume Match Analysis ======" << endl;
    cout << "\nMatched Skills:\n";
    for(const string &skill : matchedSkills) {
        cout << skill << endl;
    }

    cout << "\nMissing Skills:\n";
    for(const string &skill : missingSkills) {
        cout << skill << endl;
    }
    
    cout << "\nMatch Score: ";
    cout << fixed << setprecision(2);
    cout << score << "%" << endl;

    return 0;
}