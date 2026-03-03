#include  <bits/stdc++.h>
using namespace std;

class TextProcessor{
private:
    unordered_set<string> stopWords;
public:
    TextProcessor() {
        stopWords = {
            "and", "the", "for", "with", "a", "an",
            "to", "of", "in", "on", "at", "by",
            "is", "are", "looking", "i", "am"
        };
    }

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
        resumeFreq.clear();
        jobSet.clear();
        matchedSkills.clear();
        missingSkills.clear();
        totalPoints = 0;

        for(const string &word : resume) {
            resumeFreq[word]++;
        }

        for(const string &word : job) {
            jobSet.insert(word);
        }

        for(const string &skill : jobSet) {
            if(resumeFreq.count(skill)) {
                matchedSkills.push_back(skill);

                int freq = resumeFreq[skill];
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

class Scorer {
public:
    double calculateScore(int totalPoints, int jobCount) {
        double score = 0;
        if(jobCount > 0) {
            score = (double)totalPoints / (3 * jobCount) * 100;
        }
        return score;
    }
};

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

    vector<string> resumeProcessed = tp.process(resume);
    vector<string> jobProcessed = tp.process(job);

    sm.match(resumeProcessed, jobProcessed);

    vector<string> matchedSkills = sm.getMatched();
    vector<string> missingSkills = sm.getMissing();

    int totalPoints = sm.getTotalPoints();
    int jobCount = sm.getJobSkillCount();

    double score = scorer.calculateScore(totalPoints, jobCount);

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