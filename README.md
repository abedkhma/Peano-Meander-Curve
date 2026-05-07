# Peano-Meander-Curve

A university project developed at the **Technical University of Munich (TU Munich)**  
as part of the *Praktikum Rechnerarchitektur (ERA)* course — Task A215 (Image Processing).

The program generates space-filling **Peano-Meander Curves** of a specified degree  
and outputs them as an **SVG file**.

---

## What is a Peano-Meander Curve?

A Peano-Meander Curve is a planar, space-filling curve that passes through every corner  
of a unit square. Through an iterative process, curves of higher degrees (n=1..8) can be  
constructed from the base curve. The output is a connected sequence of (x, y) coordinates  
rendered as an SVG line drawing.

---

## Tech Stack

| Component | Technology |
|---|---|
| Core algorithm | x86-64 Assembly (Intel syntax, SSE extensions) |
| Framework & I/O | C (main.c) |
| Output format | SVG |
| Reference implementation | C (Vergleich/cimp.c) |
| Build system | Makefile |
| Platform | GNU/Linux 64-bit |

---

## Project Structure
Implementierung/
├── peanoM.S          # Core Peano-Meander algorithm in x86-64 Assembly
├── main.c            # C framework: input validation, SVG output, memory management
├── Makefile          # Build configuration
├── peano.sh          # Helper script
├── Vergleich/        # Reference C implementation for benchmarking
│   ├── cimp.c
│   └── peano.h
└── Zeitmessung/      # Benchmarking / performance measurement
└── main.c
Ausarbeitung/         # Written report (LaTeX)
Vortrag/              # Presentation slides (PDF)

---

## How to Run

**Step 1 — Compile**
```bash
cd Implementierung
make
```

**Step 2 — Run**
```bash
./main <degree>
```
Where `<degree>` is a number between **1 and 8** (inclusive).

**Step 3 — View Output**

A file `graph.svg` will be generated. Open it with:
```bash
firefox graph.svg
```

**Help**
```bash
./main --help
```

---

## Academic Context

- **University:** Technical University of Munich (TU Munich)
- **Course:** Praktikum Rechnerarchitektur (ERA)
- **Chair:** Lehrstuhl für Rechnerarchitektur und Parallele Systeme
- **Task:** A215 — Peano-Meander-Kurven (Image Processing)
- **Implementation:** Iterative x86-64 Assembly with SSE extensions
- **Includes:** Performance benchmarking vs. C reference implementation

---

## Author
## Team

This project was developed as a group project by a team of 3 students at TU Munich:

- [Abdalla Mahamid](https://github.com/abedkhma)
- Marsel Ivanov Kolovski
- Rafiq Nasrallah