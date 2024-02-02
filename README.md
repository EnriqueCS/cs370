# Project Structure Overview

This project is organized into four primary directories: `Monolith`, `Readings`, `Syllabus`, and `WeeklyReports`. Each directory serves a distinct purpose in the context of the project.

## Directories

- **Monolith**: Contains core project files. A separate `README.md` within this folder explains the specific rationale behind its structure. Note that some large files in the `Monolith` directory are not included in the repository due to their size but are present on my local machine.

- **Readings**: Includes materials and resources for reference.

- **Syllabus**: Outlines the scope of the project and the timeline for its implementation.

- **WeeklyReports**: This directory holds the weekly progress reports of the project. Each report, named in the format `MMReportDD-DD.md`, provides a comprehensive overview of the developments, challenges, and any significant changes in the project's trajectory for that week. These reports are vital for tracking the project's progress and ensuring alignment with the project goals and timelines.

# Potential Metrics for Evaluating Hashing Algorithms

When assessing hashing algorithms on modern computing systems, particularly for large tables, it's crucial to consider the following architectural effects:

- **Cache Utilization**: Performance is heavily influenced by how algorithms leverage the cache hierarchy. Effective cache use minimizes cache misses, enhancing speed.

- **Memory Bandwidth**: Algorithms need to efficiently manage memory bandwidth. Optimizing data movements can lead to better performance due to minimized bandwidth bottlenecks.

- **Concurrency and Parallelism**: The ability to exploit multicore processors through parallel execution paths significantly affects performance. This involves efficient synchronization and data sharing across cores.

- **Instruction-Level Efficiency**: The match between algorithm operations and the processor's instruction set can accelerate performance, especially if specialized instructions are utilized.

- **Memory Access Patterns**: Favoring sequential over random access and exploiting locality of reference can improve performance by better aligning with memory hierarchy.

- **Large Table Handling**: The algorithm's approach to managing very large tables impacts performance, particularly in terms of scaling, memory overhead, and minimizing cache thrashing.

These metrics collectively provide a framework for evaluating the space-time tradeoffs of hashing algorithms in the context of modern computing architectures.