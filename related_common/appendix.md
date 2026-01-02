# PHARMOS CPR0003319 - Discount Workflow Optimization

## Overview

This repository contains analysis and implementation documentation for CPR0003319, a Change Production Release that optimizes discount data transfer in the PHARMOS pharmaceutical distribution system. The primary goal is to consolidate discount distribution from a per-branch model (20 duplicate transfers) to a per-country model using Branch 0 as a central consolidation point, achieving 95% reduction in data duplication and overnight batch processing time.

The system manages discount and rebate workflows for pharmaceutical distribution across 8 European countries (DE, AT, CH, FR, BG, HR, RS, and regional), handling customer-specific pricing, payment terms, pharmacy group discounts, and regulatory compliance including narcotics tracking (NTTD).

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Core Technology Stack
- **Database**: Informix (SQL-based queries with embedded SQL in C/C++)
- **Backend Languages**: C/C++ (MFC applications, batch programs, embedded SQL via EXEC SQL)
- **Service Layer**: Apache Thrift (cross-language RPC framework for service interfaces)
- **Platforms**: Windows (GUI applications), Unix/Linux (batch processing)
- **Build System**: Ant with Ivy for dependency management

### Package Structure
The system consists of three main package groups:

1. **CSC_LOAD** (`pharmos.outbound.csc_load`): Batch loaders that write discount data from ZDP (Central Data Pool) to KSC database during overnight processing. Key files include `loadconditions.cxx/sh`, `loadcstdiscacc.cxx`, and `loadrange.cxx`.

2. **CSC_CORE** (`pharmos.outbound.csc_core_applications`): Runtime applications that read discount data during order processing. Contains multiple layers:
   - `pxdb/`: Database access layer with SQL cursors
   - `pxverbund/`: Core discount calculation engine
   - `libcsc/`: Business logic libraries (discountaccount, pricesanddiscounts modules)
   - `thrift/`: Service handlers for external API access
   - `aapserv/`: Article and customer service components

3. **CDM** (`pharmos.base.cdm`): Central Data Maintenance - master data management for articles, prices, and discounts. Acts as the source system for discount data flowing to CSC packages.

### Data Flow Architecture
```
ZDP (Source: ZDISCOUNT - no BranchNo) 
    → CSC_LOAD (adds BranchNo during load)
    → KSC Database (LDDISCOUNT with BranchNo)
    → CSC_CORE (reads for order processing)
```

### Key Database Tables
- **Outbound (CSC)**: discount, cstdiscountcont, discountgrp, discountgrpmem, discountlist, cstdiscacc
- **Inbound (CDM)**: cdiscount, cdiscountmodes, rebate, rebatesync, quota tables

### Critical Implementation Pattern
SQL queries throughout the codebase filter by `BRANCHNO = :d->BRANCHNO`. The optimization requires changing these to use `BRANCHNO = 0` for centralized discount data while maintaining actual branch numbers for operational data.

## External Dependencies

### Third-Party Libraries
- **Apache Thrift** (v0.12.0+): RPC framework for service interfaces. Source retrieved via Ivy, built locally for Windows and AIX platforms. Located at `pharmos.3rd_party.thrift_11dec/`.

### Database Systems
- **Informix**: Primary database for discount tables, accessed via embedded SQL (EXEC SQL) in C++ files. Tables use specific column types (INT16, INT32, DECIMAL, CHAR).

### External Systems Integration
- **ZDP (Zentrales Datenpool)**: Central Data Pool - source of discount data transfers
- **KSC (Kunden Service Center)**: Customer Service Center backend receiving discount data
- **APX**: Job scheduling system for batch processing configuration

### Country-Specific Configurations
Shell scripts with country variants exist for: AT (Austria), BG (Bulgaria), CH (Switzerland), DE (Germany), FR (France), HR (Croatia), RS (Serbia). Configuration located in `environment/*/ksc/load/proc/` directories.

### Web Utilities
PHP/JavaScript web utilities for monitoring CSC services, located at `dev/doc/utilities/websites/`. Used for port scanning, version overview, and core dump monitoring across production environments.