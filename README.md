# 🚀 HR Management & Payroll System (HR-C)

A high-performance corporate HR and payroll command-line system built in pure **C Language**. The system emphasizes manual memory management (`malloc`/`free`), pointer manipulation, data structure normalization, and modular architecture aligned with Brazilian labor calculation standards (CLT).

---

## 🛠️ Software Engineering & Architectural Highlights

This project was engineered to demonstrate robust system-level concepts and modern software design principles:

* **DRY Principle (Don't Repeat Yourself):** Centralized payroll logic inside a dedicated `gerarHolerite` engine. This eliminates code duplication across individual queries, general company reports, and batch processing.
* **Data Normalization:** Complete decoupling between the `Funcionario` (Employee) and `Cargo` (Position/Role) entities using independent linked lists, simulating relational database mapping in memory.
* **Resilient Batch Processing:** The multi-ID lookup module applies partial error handling. If an operator requests invalid IDs, the system continues processing valid records and logs explicit warnings without crashing or aborting the batch.
* **Memory Management & Hygiene:** Strict pointer tracking and manual memory deallocation via `free()` to prevent memory leaks during record deletion operations.
* **Cross-Platform Console Compatibility:** Cleaned and standardized text output buffers to ensure seamless rendering across Windows PowerShell, Linux, and macOS terminals.

---

## 📋 System Features

1. **Employee Management (CRUD):** Dynamic LIFO (Stack) insertion, full record scanning, updating employee details, and safe node removal with memory deallocation.
2. **Job Position Configuration:** Dynamic configuration of baseline salaries (floors) per role, acting as a single source of truth for HR calculations.
3. **CLT Payroll Module:**
   * Automated hourly rate calculation based on the standard 220-hour monthly benchmark (44h workweek).
   * Overtime calculation with a legal 50% multiplier ($1.5\times$).
   * INSS social security tax deduction simulation.
   * Generation of individual pay stubs, full corporate payroll reports, and batch queries (up to 10 IDs).

---
## 🔮 Roadmap & Future Enhancements

1. **[ ] Implement file persistence (fopen, fprintf, fread) to save and restore state across system sessions.
2. **[ ] Adapt the payroll engine for the Constitutional Amendment No. 141/2026 roadmap (gradual transition to 42-hour and 40-hour workweeks).
3. **[ ] Object-Oriented refactoring and rewrite in Python with unit testing.

---

## ⚙️ Compilation & Execution

Ensure you have a GCC compiler installed.

```bash
# Clone the repository
git clone [https://github.com/asta-mentality/sistema-RH-c.git](https://github.com/asta-mentality/sistema-RH-c.git)

# Navigate to the project directory
cd sistema-RH-c

# Compile the source code
gcc sistemaRH.c -o sistemaRH

# Run the executable (Windows PowerShell)
.\sistemaRH.exe
