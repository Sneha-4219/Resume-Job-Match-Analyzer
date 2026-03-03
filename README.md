# Resume – Job Match Analyzer (C++ | STL | OOP | Hashing)

---

## 🎯 Goal

Create a CLI-based system that analyzes resume and job description text, extracts meaningful skills, and computes a weighted match score using hashing and clean OOP design.

If you understand everything on this page, you can confidently explain this project in an interview.

---

# RESUME — JOB MATCH ANALYZER (FINAL)

---

## 🎯 Purpose

This project demonstrates how core DSA concepts can be applied to a real-world text processing problem.

It focuses on:

- String normalization  
- Tokenization  
- Hash-based frequency counting  
- Weighted scoring  
- Clean separation of concerns  

If you can explain this architecture clearly, you are internship-ready.

---

## 🔔 Core Concepts Used

This project locks in the following concepts:

- String traversal
- Character handling
- Hashing (`unordered_map`, `unordered_set`)
- Frequency counting
- Weighted scoring
- OOP design principles
- Time complexity reasoning

---

## 🧩 Architecture Overview

The project is divided into three independent modules:

### 🔹 TextProcessor

Responsible for:

- Converting text to lowercase
- Preserving relevant symbols (`+`, `#`)
- Removing unnecessary punctuation
- Tokenizing words manually
- Removing stopwords

Single responsibility: **Text preprocessing**

---

### 🔹 SkillMatcher

Responsible for:

- Building frequency map of resume skills
- Building unique job skill set
- Matching skills
- Applying capped weighted scoring logic
- Tracking matched and missing skills

Single responsibility: **Skill comparison logic**

---

### 🔹 Scorer

Responsible for:

- Calculating final percentage score
- Keeping scoring formula independent from matching logic

Single responsibility: **Scoring strategy**

---

## 🔁 Processing Pipeline

Input  
→ Normalize text  
→ Tokenize  
→ Remove stopwords  
→ Build resume frequency map  
→ Build unique job skill set  
→ Apply weighted matching  
→ Compute final score  

Each stage has a single responsibility.

---

## 🧠 Scoring Logic (MEMORIZE THIS)

Each job skill contributes up to **3 points** (cap = 3).

For each skill: 

```SkillContribution = min(frequency_in_resume, 3)```

Final Score:

```Score = (TotalPoints / (Cap × JobSkillCount)) × 100```


Where:

- TotalPoints = sum of capped contributions
- Cap = 3
- JobSkillCount = number of unique job skills

This prevents score inflation and reflects skill depth.

---

## ⏱ Time & Space Complexity

Let:

- n = words in resume
- m = words in job description

### Time Complexity

- Text processing → O(n + m)
- Hash map construction → O(n)
- Matching → O(m)

Overall:
O(n + m)


### Space Complexity

- Frequency map → O(n)
- Job set → O(m)

Efficient and scalable.

---

## ⭐ Why unordered_map Over map?

- `unordered_map` → O(1) average lookup (hashing)
- `map` → O(log n) (Red-Black Tree)

Since ordering is not required, hashing is preferred for faster lookup.

---

## 🧪 Sample Input

**Resume:** SQL SQL SQL Python
**Job Description:** SQL Python C++

**Output:**

<pre>```====== Resume Match Analysis ======

Matched Skills:
python
sql

Missing Skills:
c++

Match Score: 44.44%```</pre>


---

## 🎯 Learning Outcomes

This project reinforces:

- Tradeoffs between `map` and `unordered_map`
- Frequency-based scoring logic
- Avoiding naive binary matching
- Clean separation of concerns
- Writing modular C++ code
- Explaining complexity clearly

---

## 💡 Future Extensions

- Phrase detection (e.g., "data structures", "machine learning")
- Partial matching (JS ↔ JavaScript)
- Multi-resume ranking system
- GUI or Web version
- TF-IDF based weighting

---

## ✅ Final Reminder

This project is not about fancy UI.

It is about:

- Clean thinking  
- Correct data structures  
- Proper separation of concerns  
- Clear explanation under interview pressure  

If you can defend every design decision here,  
you are strong for internship interviews.

---

👩‍💻 Built as part of a Data Structures & Algorithms mastery journey.