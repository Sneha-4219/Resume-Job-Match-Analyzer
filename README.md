# Resume – Job Match Analyzer (C++ | STL | OOP | Hashing)

## 📖 Overview

A CLI-based Resume–Job Match Analyzer built using C++ and STL.  
The tool processes resume and job description text, extracts skills, and computes a weighted match score.

This project demonstrates:

- String processing and normalization
- Hashing using `unordered_map` and `unordered_set`
- Frequency-based weighted scoring
- Clean OOP architecture
- Time complexity awareness

---

## 🚀 Features

- Smart normalization (handles C++, C#, Node.js)
- Manual tokenization (no regex used)
- Stopword filtering
- Frequency-based weighted matching
- Capped scoring logic (max 3 points per skill)
- Clean modular design:
  - `TextProcessor`
  - `SkillMatcher`
  - `Scorer`

---

## 🧠 How It Works

1. Normalize input text  
   - Convert to lowercase  
   - Preserve relevant symbols (+, #)  
   - Remove unnecessary punctuation  

2. Tokenize into words

3. Remove stopwords (e.g., "and", "the", "for")

4. Build frequency map of resume skills using `unordered_map`

5. Compare against unique job skills using `unordered_set`

6. Compute weighted score with capped contribution per skill

---

## 📊 Scoring Formula

Each job skill contributes up to 3 points (cap = 3).
Score = (TotalPoints / (Cap × JobSkillCount)) × 100

Where:

- `TotalPoints` = sum of min(frequency, 3) for matched skills
- `Cap` = 3
- `JobSkillCount` = number of unique job skills

---

## ⏱ Time Complexity

Let:

- n = number of words in resume
- m = number of words in job description

Operations:

- Text processing → O(n + m)
- Hash map construction → O(n)
- Matching → O(m)

Overall Complexity:
O(n + m)

---

## 🛠 Technologies Used

- C++
- STL (Standard Template Library)
- unordered_map
- unordered_set
- OOP design principles

---

## 🧪 Sample Input

Resume:
SQL SQL SQL Python
Job Description:
SQL Python C++
Output:
====== Resume Match Analysis ======

Matched Skills:
python
sql

Missing Skills:
c++

Match Score: 44.44%


---

## 🏗 Architecture

The project is structured into three main components:

### 🔹 TextProcessor
- Handles normalization
- Tokenization
- Stopword filtering

### 🔹 SkillMatcher
- Builds frequency map
- Matches skills
- Calculates total weighted points

### 🔹 Scorer
- Calculates final percentage score
- Keeps scoring strategy independent

---

## 🎯 Learning Outcomes

This project reinforced:

- Hash-based data structures
- Tradeoffs between `map` and `unordered_map`
- Frequency counting patterns
- Clean separation of concerns
- Weighted scoring strategies
- Modular OOP design in C++

---

## 💡 Future Improvements

- Phrase detection (e.g., "data structures", "machine learning")
- Partial matching (e.g., JS ↔ JavaScript)
- Multi-resume ranking system
- GUI or web-based interface

---

## 👩‍💻 Author

Built as part of Data Structures & Algorithms learning journey.