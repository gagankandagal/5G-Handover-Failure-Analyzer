# 5G Handover Failure Analyzer

A C++ and Flask-based web application for analyzing 5G handover performance and identifying potential handover failures from CSV network data.

The system processes handover records, calculates performance statistics, identifies failure reasons, performs cell-to-cell analysis, and presents the results through an interactive web dashboard.

---

## Overview

In a 5G network, handover is the process of transferring a User Equipment (UE) connection from one serving cell to another.

Handover failures can affect:

- Network reliability
- User experience
- Mobility performance
- Radio resource management
- Cell-to-cell connectivity
- Overall network performance

This project provides a lightweight analysis platform that takes handover data in CSV format and generates an analytical report.

The core analysis is implemented in **C++**, while the web dashboard is implemented using **Python Flask**.

---

## Key Features

### 1. CSV-Based Handover Analysis

Upload a CSV file containing handover records.

The analyzer processes parameters such as:

- Record ID
- Timestamp
- Source Cell
- Target Cell
- RSRP
- RSRQ
- SINR
- Handover Duration
- Handover Result

---

### 2. Handover Performance Analysis

The system calculates:

- Total handovers
- Successful handovers
- Failed handovers
- Success rate
- Failure rate
- Average RSRP
- Average RSRQ
- Average SINR
- Average handover duration

---

### 3. Failure Reason Analysis

The analyzer classifies failed handovers based on radio and timing conditions.

Example failure categories include:

- Very Weak RSRP
- Weak RSRP
- Poor RSRQ
- Very Low SINR
- Low SINR
- High Handover Duration

The dashboard displays the failure-reason distribution graphically.

---

### 4. Cell-to-Cell Analysis

The project analyzes individual source-to-target cell combinations.

For each cell pair, the system calculates:

- Source Cell
- Target Cell
- Number of Attempts
- Successful Handovers
- Failed Handovers
- Success Rate
- Failure Rate

This helps identify cell pairs that experience frequent handover failures.

---

### 5. Interactive Dashboard

The Flask web interface provides:

- KPI cards
- Success vs Failure chart
- Radio measurement chart
- Handover duration chart
- Failure reason chart
- Cell-to-cell failure rate chart
- Handover records table
- Failed handover records
- Search functionality
- Source-cell filtering
- Target-cell filtering
- Success/Failure filtering

---

### 6. Search and Filtering

Users can search handover records using:

- Record ID
- Cell ID
- Other displayed record information

The dashboard also supports filtering by:

- Source Cell
- Target Cell
- Handover Result

A reset option allows the filters to be cleared.

---

### 7. Report Export

The generated analysis can be downloaded as:

- CSV report
- JSON report

This makes the analysis results useful for further processing or documentation.

---

## System Architecture

```text
                    ┌─────────────────────┐
                    │     CSV Dataset     │
                    │  Handover Records   │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │    C++ Analyzer     │
                    │                     │
                    │ Data Reader         │
                    │ Handover Analyzer   │
                    │ Failure Analyzer    │
                    │ Cell Statistics     │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │   Analysis Report   │
                    │                     │
                    │ JSON                │
                    │ CSV                 │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │    Flask Backend    │
                    │                     │
                    │ Upload              │
                    │ Processing          │
                    │ Report Loading      │
                    │ Downloads           │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │   Web Dashboard     │
                    │                     │
                    │ Charts              │
                    │ KPIs                │
                    │ Search              │
                    │ Filters             │
                    │ Tables              │
                    └─────────────────────┘
