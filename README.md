# MWDDS — Steady-State Genetic Algorithm for the Minimum Weight Directed Dominating Set

M.Tech dissertation research. A **Steady-State Genetic Algorithm (SSGA)** that solves the
**Minimum Weight Directed Dominating Set (MWDDS)** problem, using four heuristic repair
operators (H1–H4) and comparing the results against the ABC and IWO metaheuristics from the
literature.

---

## 1. Problem

Given a **directed graph** `G = (V, E)` where every node has a positive weight, find a subset
`D ⊆ V` of minimum total weight such that **every node is either in `D` or is pointed to by at
least one node in `D`** (i.e. `D` is a dominating set under directed out-edges).

- Objective: minimise `Σ weight(v)` for `v ∈ D`.
- A solution is a binary chromosome of length `|V|` (1 = node selected).
- Infeasible if any node is left "free" (neither selected nor dominated).

---

## 2. Algorithm Flow

Single C program, entry point [`src/M0.c`](src/M0.c) `main()`. All other `.c` files are
`#include`d directly into it (one translation unit, no separate linking).

```
read input_files.txt  →  for each graph file:
  ├─ parse graph → Nodeno, nodeweightarr[], directed_graph[][],
  │                adjacency_list[][], parent_nodes[][]
  │
  ├─ POPULATION INIT  (pop_size = 200)
  │     build candidate → repairing() → minimization() → fitness
  │
  ├─ GA LOOP  (MAX_GEN = 10000)
  │     tournament select (prob_select)
  │     → crossover: fitness-based or k-point (Pc, k_points=3)
  │     → mutation (Pm)
  │     → repairing()  → minimization()
  │     → steady-state replace if offspring is better
  │
  └─ record best fitness + runtime → hit_and_trail.txt
```

Per-candidate pipeline: **construct → repair (make feasible) → minimize (strip redundant
nodes)**.

### Components
| File | Role |
|------|------|
| [`src/M0.c`](src/M0.c) | `main()` + GA loop (population init, crossover, mutation, selection) |
| [`src/global_variables.c`](src/global_variables.c) | all tunable parameters + `check()` feasibility validator |
| [`src/outdegree.c`](src/outdegree.c) | out-degree computation (used by minimizing) |
| [`src/heuristics_H1.c`](src/heuristics_H1.c) … `H4.c` | 4 greedy construction heuristics (weighted-successor score, `score = (white_successor_sum + w·color) / w`) |
| [`src/repairing.c`](src/repairing.c) | repair operator — dispatches to the chosen heuristic to make a chromosome feasible |
| [`src/redundant_repair.c`](src/redundant_repair.c) | repair helper |
| [`src/second_stage_redundant_find.c`](src/second_stage_redundant_find.c) | finds removable (redundant) nodes |
| [`src/minimization_stage_one.c`](src/minimization_stage_one.c), [`src/minimize_heuristics.c`](src/minimize_heuristics.c), [`src/minimizing.c`](src/minimizing.c) | minimization stage (removes redundant selected nodes without breaking domination) |

### Approach labels (used in the dissertation tables)
The same run is reported under a `G` label per repair heuristic:

| Label | Repair heuristic |
|-------|------------------|
| G1 | H1 |
| G2 | H2 |
| G3 | H3 |
| G4 | H4 |

`ABC` and `IWO` are baseline results taken from the literature (Jan 2022).

### Key parameters — [`src/global_variables.c`](src/global_variables.c)
| Param | Value | Meaning |
|-------|-------|---------|
| `pop_size` | 200 | population size |
| `MAX_GEN` | 10000 | generations |
| `Pc` | 0.9 | crossover probability (genetic vs random) |
| `prob_select` | 0.8 | tournament selection probability |
| `Pm` | 0.01 | mutation probability |
| `PPh` | 0.9 | repair-vs-random choice on init |
| `k_points` | 3 | k-point crossover points |

---

## 3. Build & Run

```bash
gcc -O2 -o mwdds src/M0.c -lm
./mwdds
```

No dependencies beyond `libc` / `libm`.

- Reads the list of graph files from `src/input_files.txt` (one path per line).
- Writes per-instance results (heuristic, time, filename, best value) to `hit_and_trail.txt`.
- Prints best fitness + runtime per instance to stdout.

> **Note:** `src/input_files.txt` currently holds absolute Linux paths
> (`/home/akhil/MWDDS_akhil/...`). Rewrite these to local `MWDDS_data/...` paths before running
> on this machine. The prebuilt binaries (`src/a.out`, `me`, `my`, `memx`, …) are Linux ELF and
> will not run on macOS — recompile.

---

## 4. Datasets — `MWDDS_data/`

Three graph families, each grouped as `(|V|, |E|)` with **10 instances per group**:

| Folder | Type | Instances |
|--------|------|-----------|
| `MWDDS_data/UDG/` | Unit Disk Graphs | 12 groups |
| `MWDDS_data/T1/`  | Type-1 | 53 groups |
| `MWDDS_data/T2/`  | Type-2 | 53 groups |

Total: **118 groups × 10 = 1180 instances.**

Graph file format is described in [`MWDDS_data/MWDDS_data_format.txt`](MWDDS_data/MWDDS_data_format.txt):
node count, per-node weights, then a directed adjacency matrix (`a→c` means row `a`, col `c` = 1;
no self-loops, no parallel edges).

---

## 5. Results — `result/`

Raw run logs (table format, one line per instance):

```
H1: 84.680   84   /.../UDG/800/150/graphS0N800.txt :670
└┬┘  └──┬──┘ └┬┘       └────────┬────────┘          └┬┘
 type  time  cum          dataset / |V| / |E|      best fitness
```

The reported table value `Gx` = **mean best-fitness over the 10 instances** of a group;
`Gx_ET` = mean runtime over the group. These correspond to Tables 5.1 (UDG), 5.2 (T1) and
5.3 (T2) of the dissertation.

### Regenerated / verified artifacts (in `result/`)
| File | Contents |
|------|----------|
| `result/regenerated_G1-G4.csv` | all 118 groups: G1–G4 fitness + exec-time + instance count |
| `result/all_instances_H1-H4.txt` | all 1180 instances, per-instance best-fitness for H1–H4, with a `G(avg)` row per group |

These were regenerated from the raw logs and cross-checked against the dissertation tables —
all group averages match (one cell, T1 150/150 G3, is `2237.4` here vs a `2237.5` typo in the PDF).

---

## 6. Repository Layout

```
Mtech-reserach_MWDDS/
├── README.md                 ← this file
├── src/                      ← source + build artifacts + logs
│   ├── M0.c                  ← main (compile this)
│   ├── global_variables.c
│   ├── outdegree.c
│   ├── heuristics_H1..H4.c
│   ├── repairing.c  redundant_repair.c  second_stage_redundant_find.c
│   ├── minimization_stage_one.c  minimize_heuristics.c  minimizing.c
│   ├── input_files.txt       ← dataset list (fix paths before running)
│   └── dustbin/ …            ← old versions / scratch (not used)
├── MWDDS_data/               ← UDG, T1, T2 graph instances + format spec
└── result/                   ← run logs + regenerated tables
```

### Files NOT part of the build (safe to ignore / prune)
- **Dead source** (commented out of `M0.c`, never included): `redundant.c`,
  `redundant_find_function.c`, `minimization_stage.c`, `minimization_stage_two.c`,
  `sorting_algorithm.c`, `leak_detector_c.*`.
- **Old versions:** entire `src/dustbin/`, `dustbin_M0_main.c`, `dustbin_crossover.c`.
- **Stale binaries (Linux ELF):** `a.out`, `me`, `my`, `memx`, `memtest`, `*.o`.
- **Scratch logs:** `waste.txt`, `trash.txt`, `stage2.txt`, `leak_info.txt`,
  `results_H1*.txt`, `Untitled*`, `.DS_Store`.

---

## 7. Reproducing the Dissertation Tables

1. Compile and run on all 1180 instances (fix `input_files.txt` paths first).
2. Group the `hit_and_trail*.txt` output by `(type, |V|, |E|)`.
3. For each group, average the 10 per-instance best-fitness values → `Gx`;
   average the 10 runtimes → `Gx_ET`.
4. Compare G1–G4 against each other and against ABC/IWO (dissertation Table 5.4:
   win / tie / loss counts, columns Bv / Ev / Wv).
