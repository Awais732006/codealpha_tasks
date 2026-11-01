# CodeAlpha C++ Projects

Three completed console projects covering Tasks 1, 3 and 4 of the supplied instructions. Each folder is an independent program with its own `main.cpp`. Compile and run one project at a time.

## Contents

| Folder | Assigned task | Main concepts |
| --- | --- | --- |
| CodeAlpha_CGPA_Calculator | Task 1 | Structures, vectors, weighted averages, input validation |
| CodeAlpha_Sudoku_Solver | Task 3 | 2D arrays, recursion, backtracking |
| CodeAlpha_Banking_System | Task 4 | Customer, Account and Transaction classes, vectors, menus |

Each project contains a README with its requirements, operation, example and explanation. `TEST_RESULTS.txt` contains actual test inputs and terminal output. `test_projects.py` reproduces the tests.

## Run in Microsoft Visual Studio (Windows)

1. Open **Visual Studio**. The **Desktop development with C++** workload must be installed.
2. Choose **Create a new project > Console App > C++**.
3. Give the project the corresponding name from the table.
4. Replace the generated `.cpp` file's contents with the selected project's `main.cpp`.
5. Press **Ctrl+F5** to build and run.
6. Enter input as shown in that project's README.

Use a separate Visual Studio project for each program. Combining the three files in one project causes multiple `main` function errors. No extra libraries or packages are required; the source uses standard C++11.

## Run with g++

Inside any one project folder:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic main.cpp -o app
```

On Windows, run `app.exe` (or `./app.exe` in PowerShell). On Linux/macOS, run `./app`.

## Verify all projects

From this package's root folder, with Python 3 and g++ installed:

```sh
python test_projects.py
```

The test script compiles every project, runs 17 test scenarios, checks results, and updates `TEST_RESULTS.txt`. Sudoku verification checks every row, column and 3x3 box and confirms all original clues are preserved. Test compilation treats compiler warnings as errors.

## Submission steps from the supplied instructions

1. Create separate GitHub repositories using the exact project folder names in the table, which follow `CodeAlpha_ProjectName`.
2. Add each project's `main.cpp` and its README. Review the code and understand the explanation before recording.
3. Record a short demonstration of each program: show the problem, explain the main functions, run a normal example, then show an error being handled.
4. Follow the instructions to post your internship status and demonstration on LinkedIn, tagging CodeAlpha and including the relevant repository link.
5. Submit the links through the form provided in your WhatsApp group within your assigned deadline.

This package prepares the programs and explanations. GitHub repositories, LinkedIn posts, videos and submission-form entries still need to be completed. Task 2 (Login and Registration) is not included; the document permits any two or three of the four tasks.

## Scope

These are beginner-friendly educational console programs. The banking simulator keeps data in memory until exit; it does not implement real customer authentication, persistent storage or production banking services. The task does not explicitly require persistent banking storage. The Sudoku GUI is optional and is not included. The CGPA calculator uses numeric grade points on a 4.0 scale; use the grade points assigned by your university rather than raw marks.
