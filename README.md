# TI301 - Study of Markov Graphs

**Course:** Algorithms and Data Structures 2  
**Project:** Computer Science and Mathematics Project  

## 👥 Team Members
*   **Jalil Bellahcen**
*   **Louis Mouriez**
*   **Clément Moussy**

---

## 📝 Project Overview
This project is a C implementation designed to analyze Markov chains. It combines graph theory algorithms with matrix algebra to extract structural characteristics and probability evolutions of Markov graphs.

The project is divided into three main parts:
1.  **Data Structures & Visualization:** Storing graphs and validating Markov properties.
2.  **Structural Analysis:** Grouping vertices into Strongly Connected Components (SCC) using **Tarjan's Algorithm** and generating **Hasse Diagrams**.
3.  **Probabilistic Analysis:** Using matrix multiplication to determine stationary distributions and graph periodicity.

---

## 📂 Project Structure

The project is modularized to ensure code reusability and clarity:

*   **`main.c`**: Entry point for Part 1 (Graph creation & validation).
*   **`main2.c`**: Entry point for Part 2 (Tarjan's Algorithm & Hasse Diagram).
*   **`main3.c`**: Entry point for Part 3 (Matrix calculations & Statistics).
*   **`utils.c / .h`**: Core data structures (Adjacency Lists, Linked Lists, Cells) and file I/O functions.
*   **`matrix.c / .h`**: Mathematical operations (Matrix creation, multiplication, difference calculation).
*   **`hasse.c / .h`**: Logic for Hasse Diagrams, redundancy removal, and partition analysis.
*   **`data/`**: Directory containing input `.txt` files (e.g., `exemple1.txt`).

---

## 🚀 Features Implemented

### Part 1: Graph Representation
*   **Adjacency List:** Efficient memory storage for sparse graphs.
*   **File Parsing:** Automated graph loading from standardized text files.
*   **Markov Validation:** Verifies if the sum of outgoing probabilities for each vertex equals 1 (with floating-point tolerance).
*   **Visualization:** Auto-generation of **Mermaid** code for graph visualization.

### Part 2: Connectivity (Tarjan & Hasse)
*   **Tarjan's Algorithm:** Implementation of the DFS-based algorithm to find Strongly Connected Components (Classes).
*   **Class Classification:** Identification of **Transient**, **Persistent**, and **Absorbing** states.
*   **Hasse Diagram:**
    *   Construction of links between classes.
    *   **Transitivity Optimization:** Removal of redundant links to simplify the diagram.
    *   Mermaid export for the Hasse diagram.

### Part 3: Matrices & Distributions
*   **Matrix Operations:** Conversion from Adjacency List to Transition Matrix.
*   **Evolution:** Calculation of probability distributions over time ($M^n$).
*   **Stationary Distribution:** Logic to detect convergence of probabilities.
*   **Periodicity (Bonus):** GCD-based logic to determine the period of a class.

---

## ⚙️ Repository & Compilation

The project uses **CMake** for the build process.

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-url>
    cd <your-repo-folder>
    ```

The compilation generates three executables corresponding to the different stages of the project:
*   `TI_301_PJT` (Part 1)
*   `TI_301_PJT_part2` (Part 2)
*   `TI_301_PJT_part3` (Part 3)

---

## 🤖 AI Usage Statement

As permitted by the project guidelines, AI tools (ChatGPT/GitHub Copilot) were used for:
*  **Debugging:** Assisting in resolving pointer logic errors within the linked lists.
*  **Code Explanation:** Clarifying the recursive steps required for Tarjan's algorithm.
*  **Documentation:** Writing this README.md file
All logic was reviewed, understood, and integrated by the team members.
