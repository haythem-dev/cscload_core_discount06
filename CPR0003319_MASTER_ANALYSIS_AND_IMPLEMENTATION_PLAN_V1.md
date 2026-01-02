# CPR0003319 - Comprehensive Analysis & Implementation Plan
## Core Product Discount Optimization - Complete Technical Analysis

**Document Version:** 1.0  
**Analysis Date:** December 30, 2025  
**Author:** AI Deep Analysis  
**Project:** PHARMOS Discount Workflow Consolidation (CPR0003319)  
**Status:** Ready for Implementation

---

## Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Deep Understanding of CPR](#2-deep-understanding-of-cpr)
3. [Complete Impacted Files Inventory](#3-complete-impacted-files-inventory)
4. [Layer-by-Layer Analysis](#4-layer-by-layer-analysis)
5. [Database Schema & Tables](#5-database-schema--tables)
6. [Implementation Plan](#6-implementation-plan)
7. [Risk Assessment & Mitigation](#7-risk-assessment--mitigation)
8. [Testing Strategy](#8-testing-strategy)
9. [Deployment Plan](#9-deployment-plan)
10. [Appendices](#10-appendices)

---

## 1. Executive Summary

### 1.1 Problem Statement

**CPR0003319** addresses a critical architectural issue in the PHARMOS pharmaceutical distribution system where discount data is unnecessarily **duplicated 20 times** (once per branch), resulting in:

- **20x data redundancy** in the DISCOUNT database table
- **20 parallel overnight batch jobs** for identical discount data
- **Major incident** on July 1, 2025 (contact: Frank Naumann)
- **Severe performance degradation** in overnight processing
- **Excessive database storage** consumption
- **High failure risk** due to multiple parallel transfer points

### 1.2 Proposed Solution

**Centralize discount data at Branch 0 (country level)** and modify all applications to read from this single source instead of branch-specific copies.

```
BEFORE (Current):                    AFTER (Proposed):
ZDP → Branch 1-20 (20 copies)       ZDP → Branch 0 (1 copy)
      ↓                                    ↓
20x Storage + 20x Processing        1x Storage + 1x Processing
```

### 1.3 Expected Benefits

| Metric | Current | Target | Improvement |
|--------|---------|--------|-------------|
| **Data Duplication** | 20 copies | 1 copy | **95% reduction** |
| **Batch Processing Time** | 20 × T minutes | 1 × T minutes | **95% faster** |
| **Database Storage** | 20 × S GB | 1 × S GB | **95% reduction** |
| **Job Failure Risk** | 20 failure points | 1 failure point | **95% reduction** |
| **Data Consistency** | 20 sources to sync | 1 source of truth | **100% consistency** |

### 1.4 Impact Scope

| Component | Files Affected | Complexity | Priority |
|-----------|----------------|------------|----------|
| **Shell Scripts** | 6 country variants | Low | **Critical** |
| **Batch Loaders (CSC_LOAD)** | 9 programs | Medium | **Critical** |
| **Database Access (PXDB)** | 7+ SQL cursors | High | **Critical** |
| **Core Logic (PXVERBUND)** | 12 modules | High | **Critical** |
| **API Layer (THRIFT)** | 12 handlers + 14 IDL | Medium | High |
| **App Server (AAPSERV)** | 24 files | High | High |
| **Customer Library (LIBCSC)** | 74 files | High | High |
| **Database Tables** | 6 tables | Medium | Critical |
| **TOTAL** | **~153 files** | **Very High** | |

### 1.5 Key Success Metrics

- ✅ Zero data loss during migration
- ✅ No regression in discount calculations
- ✅ Performance improvement of 15-20x in overnight batch
- ✅ 95% reduction in database storage
- ✅ All regression tests pass (100%)
- ✅ Business acceptance across all 8 countries

---

## 2. Deep Understanding of CPR

### 2.1 What is CPR0003319?

**CPR (Change Production Release) 0003319** is a **discount workflow optimization project** for the PHARMOS pharmaceutical distribution system covering **8 European countries**:

- 🇩🇪 **DE** - Germany
- 🇦🇹 **AT** - Austria
- 🇨🇭 **CH** - Switzerland
- 🇫🇷 **FR** - France
- 🇧🇬 **BG** - Bulgaria
- 🇭🇷 **HR** - Croatia
- 🇷🇸 **RS** - Serbia
- 🌍 **Regional** variants

### 2.2 Current Architecture (Before CPR)

**Data Flow:**
```
ZDP (Zentrales Datenpool - Central Data Pool)
├── Source Table: ZDISCOUNT (NO BranchNo field)
│   └── Contains: Discount data for entire country
│
└── Transferred to KSC (Kunden Service Center)
    ↓
    ┌─────────────────────────────────────────┐
    │  OVERNIGHT BATCH PROCESSING (20 JOBS)   │
    ├─────────────────────────────────────────┤
    │ Job 1:  loadconditions -vz 1  → Branch 1 │
    │ Job 2:  loadconditions -vz 2  → Branch 2 │
    │ Job 3:  loadconditions -vz 3  → Branch 3 │
    │ ...                            ...        │
    │ Job 20: loadconditions -vz 20 → Branch 20│
    └─────────────────────────────────────────┘
                    ↓
    ┌─────────────────────────────────────────┐
    │   KSC DATABASE: LDDISCOUNT TABLE        │
    ├─────────────────────────────────────────┤
    │ BRANCHNO=1 | ArticleNo | DiscountPct... │
    │ BRANCHNO=2 | ArticleNo | DiscountPct... │
    │ BRANCHNO=3 | ArticleNo | DiscountPct... │
    │ ...                                      │
    │ BRANCHNO=20| ArticleNo | DiscountPct... │
    └─────────────────────────────────────────┘
           ↓↓↓ [SAME DATA × 20 TIMES] ↓↓↓
```

**Problem:** Each branch (1-20) receives **IDENTICAL discount data**, but stored separately with different BRANCHNO values, causing massive duplication.

### 2.3 Proposed Architecture (After CPR)

**Data Flow:**
```
ZDP (Zentrales Datenpool)
├── Source Table: ZDISCOUNT (NO BranchNo field)
│   └── Contains: Discount data for entire country
│
└── Transferred to KSC (Kunden Service Center)
    ↓
    ┌─────────────────────────────────────────┐
    │  OVERNIGHT BATCH PROCESSING (1 JOB)     │
    ├─────────────────────────────────────────┤
    │ Job:  loadconditions -vz 0  → Branch 0   │
    └─────────────────────────────────────────┘
                    ↓
    ┌─────────────────────────────────────────┐
    │   KSC DATABASE: LDDISCOUNT TABLE        │
    ├─────────────────────────────────────────┤
    │ BRANCHNO=0 | ArticleNo | DiscountPct... │
    └─────────────────────────────────────────┘
           ↓↓↓ [SINGLE COPY - ALL BRANCHES READ FROM HERE] ↓↓↓
           ↓
    ┌─────────────────────────────────────────┐
    │   ALL CSC APPLICATIONS (Branches 1-20)  │
    ├─────────────────────────────────────────┤
    │ Query: WHERE BRANCHNO = 0               │
    │ (instead of WHERE BRANCHNO = {1..20})   │
    └─────────────────────────────────────────┘
```

**Solution:** Load discount data **once to Branch 0**, and all applications query from this centralized source.

### 2.4 Why Branch 0?

**Branch 0 = Country-Level Aggregation**

- **Branch 1-20**: Represent individual physical branches/warehouses
- **Branch 0**: Special designation for **country-level** shared data
- **Rationale**: Discount rules are **country-specific, not branch-specific**

**Example:**
- **Germany (DE)**: Same discount rules apply to all 20 German branches
- **Austria (AT)**: Same discount rules apply to all Austrian branches
- **Current Issue**: Identical German discount data duplicated 20 times in database
- **Solution**: Store German discount data once at Branch 0

### 2.5 Critical Blocking Issue

**THE SHOW-STOPPER:** Shell script `loadconditions.sh` **explicitly blocks Branch 0**

**Location:** `pharmos.outbound.csc_load_-_/dev/src/environment/{country}/ksc/load/proc/loadconditions.sh`

**Line ~220 (CRITICAL BUG):**
```bash
# Current code REJECTS Branch 0
if [[ "$vz" == "" ]] || (( 1 != `check_numeric_parameter "$vz"` )) || [[ "$vz" == "0" ]]; then
    rc=12;
    echo "$PROCNAME: Parameter value missed or invalid value \$vz: >$vz<!"
    exit ${rc};  # ← BLOCKS BRANCH 0!
fi
```

**Required Fix:**
```bash
# Modified code ALLOWS Branch 0
if [[ "$vz" == "" ]] || (( 1 != `check_numeric_parameter "$vz"` )); then
    rc=12;
    echo "$PROCNAME: Parameter value missed or invalid value \$vz: >$vz<!"
    exit ${rc};
fi
# NOTE: Branch 0 is now allowed for country-level discount data (CPR0003319)
```

**Impact:** This single line blocks the **entire CPR implementation**. Must be fixed in **6 country variants**.

---

## 3. Complete Impacted Files Inventory

### 3.1 Package: pharmos.outbound.csc_load (Batch Loaders)

**Critical Path Components:**

| # | File | Function | BranchNo Usage | Priority | Action |
|---|------|----------|----------------|----------|--------|
| 1 | **loadconditions.sh** | Shell script executor | Validates & passes `-vz {branch}` | **CRITICAL** | Remove `vz==0` rejection at line 220 |
| 2 | **loadconditions.cxx** | Main discount loader | Inserts/updates with `BRANCHNO` | **CRITICAL** | Modify to use `BRANCHNO=0` |
| 3 | **lddiscount.h** | Target structure | Contains `short BRANCHNO` field | **INFO** | No change (structure is correct) |
| 4 | **zdiscount.h** | Source structure | NO `BRANCHNO` field | **INFO** | No change (source has no branch) |
| 5 | **loadpricelist.cxx** | Price list loader | Reads from DISCOUNT table | **CRITICAL** | Query from `BRANCHNO=0` |
| 6 | **loadshortlist.cxx** | Short list loader | Uses BranchNo | **HIGH** | Modify to use Branch 0 |
| 7 | **loadrange.cxx** | Range/group loader | Uses `-vz {branch}` parameter | **HIGH** | Use `-vz 0` |
| 8 | **loadcstdiscacc.cxx** | Customer discount account | Uses BranchNo | **HIGH** | Modify to use Branch 0 |
| 9 | **loadcstshort.cxx** | Customer short terms | Uses BranchNo | **HIGH** | Modify to use Branch 0 |
| 10 | **loadpromoquota.cxx** | Promotion quota | Discount cursor | **MEDIUM** | Review Branch usage |
| 11 | **loadpayterm.cxx** | Payment terms | Discount references | **MEDIUM** | Review |
| 12 | **loaddkopo.cxx** | Payment list | Payment/discount | **LOW** | Review |

**Shell Script Variants (MUST FIX ALL 6):**
```
pharmos.outbound.csc_load_-_/dev/src/environment/
├── oat21/at/ksc/load/proc/loadconditions.sh   (Austria)     [CRITICAL FIX]
├── och21/ch/ksc/load/proc/loadconditions.sh   (Switzerland) [CRITICAL FIX]
├── obg21/bg/ksc/load/proc/loadconditions.sh   (Bulgaria)    [CRITICAL FIX]
├── ohr21/hr/ksc/load/proc/loadconditions.sh   (Croatia)     [CRITICAL FIX]
├── ofr21/fr/ksc/load/proc/loadconditions.sh   (France)      [CRITICAL FIX]
└── ors21/rs/ksc/load/proc/loadconditions.sh   (Serbia)      [CRITICAL FIX]
```

### 3.2 Package: pharmos.outbound.csc_core_applications

#### 3.2.1 Thrift API Layer (Service Interface)

| # | File | Function | BranchNo Refs | Action |
|---|------|----------|---------------|--------|
| 1 | **customerhandler.cpp** | Customer operations | 38 references | Pass `BranchNo=0` to core |
| 2 | **orderhandler.cpp** | Order processing | 16 references | Discount calc with Branch 0 |
| 3 | **cscserviceimplpxverbund.cpp** | Service implementation | 1 reference | Pass `BranchNo=0` |
| 4 | **inquiryhandler.cpp** | Inquiry operations | 4 references | Query with Branch 0 |
| 5 | **inquirybulkhandler.cpp** | Bulk inquiry | 14 references | Branch filtering |
| 6 | **msv3handler.cpp** | MSV3 operations | 16 references | Branch in orders |
| 7 | **callbackhandler.cpp** | Callback processing | 18 references | Branch handling |
| 8 | **documenthandler.cpp** | Document handling | 28 references | Discount account access |
| 9 | **cremahandler.cpp** | CREMA processing | 7 references | Branch in orders |
| 10 | **returnshandler.cpp** | Returns handling | 4 references | Branch filtering |
| 11 | **cscservicehelper.cpp** | Helper functions | 2 references | Branch operations |
| 12 | **cscservicebatchhandler.hpp** | Batch operations | - | Branch filtering |

**Thrift IDL Files (API Contracts) - 14 files:**
```
pharmos.outbound.csc_core_applications_-_/dev/src/thrift/idl/
├── csccustomer.thrift           [30 BranchNo refs] getPricesAndDiscounts
├── csccallback.thrift           [17 BranchNo refs] Callback with branch
├── cscinquiry.thrift            [10 BranchNo refs] Inquiry methods
├── cscorder.thrift              [8 BranchNo refs]  Order discount processing
├── deliveryadvice.thrift        [7 BranchNo refs]  Delivery with discounts
├── cscmsv3.thrift               [6 BranchNo refs]  MSV3 orders
├── crema.thrift                 [6 BranchNo refs]  CREMA orders
├── documentarchiveinformation.thrift [3 refs]     Document archive
├── narcoticsarchive.thrift      [3 BranchNo refs] Narcotics archive
├── returns.thrift               [1 BranchNo ref]  Returns processing
├── shipmenttracking.thrift      [2 BranchNo refs] Shipment tracking
├── cscbase.thrift               [2 BranchNo refs] Base types
├── csctypes.thrift              Common types
└── cscservice.thrift            Service definition
```

#### 3.2.2 pxverbund Library (Core Discount Processing)

| # | Module | File | Key Functions | BranchNo Usage | Priority |
|---|--------|------|---------------|----------------|----------|
| 1 | **pxDiscount** | discount.cpp | 10+ Select methods | `BranchNo` in constructor & all queries | **CRITICAL** |
| 2 | **pxCalcDiscount** | calcdiscount.cpp | Discount calculation | Branch cascade to all methods | **CRITICAL** |
| 3 | **pxArtDiscountInfo** | artdiscountinfo.cpp | Article discount info | BranchNo in Select methods | **HIGH** |
| 4 | **pxCstDiscAcc** | ordcstdiscacc.cpp | Customer discount account | ArrayBranchNo handling | **HIGH** |
| 5 | **pxRange** | range.cpp, rangecollect.cpp | Range processing | BranchNo selections | **HIGH** |
| 6 | **pxBalanceCollect** | balancecollect.cpp | Balance collection | BranchNo, DiscountGrpNo | **MEDIUM** |
| 7 | **pxPromotionCollect** | promotioncollect.cpp | Promotion collection | BranchNo selections | **MEDIUM** |
| 8 | **pxConstimeCollect** | constimecollect.cpp | Consignment time | BranchNo, DiscountGrpNo | **MEDIUM** |
| 9 | **pxDonePromoQuotas** | donepromoquotas.cpp | Promotion quotas | BranchNo filtering | **MEDIUM** |
| 10 | **pxItemDiscount** | itmdiscount.cpp | Item discount | Branch error conditions | **LOW** |
| 11 | **pxDiscountUtil** | discountutil.cpp | Discount utilities | Discount helper functions | **LOW** |

**Critical Methods in discount.cpp (ALL require BranchNo parameter):**
```cpp
pxDiscountList::Select(const short BranchNo, long ArticleNo)
pxDiscountList::Select(const short BranchNo, long ArticleNo, long CustomerNo)
pxDiscountList::Select(const short BranchNo, long ArticleNo, short DiscountType, ...)
pxDiscountList::Select(CASCADE_*, const short BranchNo, long ArticleNo, ...)
pxDiscountList::SelectRange(const short BranchNo, long DiscountGrpNo, long CustomerNo)
pxDiscountList::SelectByCustomer(const short BranchNo, long CustomerNo, ...)
pxDiscountList::SelectByGroup(const short BranchNo, long DiscountGrpNo, ...)
pxDiscountList::SelectByManufacturer(const short BranchNo, long ManufacturerNo, ...)
// ... 10+ total selection methods requiring BranchNo parameter
```

**Required Change Pattern:**
```cpp
// BEFORE: Variable branch
int result = discountList.Select(currentBranchNo, articleNo);

// AFTER: Fixed Branch 0
int result = discountList.Select(0, articleNo);  // Branch 0 for country-level
```

#### 3.2.3 aapserv (Application Server)

| # | File | Description | BranchNo Refs | SQL Queries | Priority |
|---|------|-------------|---------------|-------------|----------|
| 1 | **artikel.cxx/h** | Article processing | 235 | 6+ discount queries | **CRITICAL** |
| 2 | **customer.cxx/h** | Customer processing | 172 | 4+ discount group queries | **CRITICAL** |
| 3 | **promo.cxx/h** | Promotion processing | 37 | Discount-related | **CRITICAL** |
| 4 | **promoinfo.cxx/h** | Promotion info | 29 | Discount info queries | **HIGH** |
| 5 | **orders.cxx/h** | Order processing | 39 | Order discount queries | **HIGH** |
| 6 | **callback.cxx/h** | Callback processing | 35 | Callback with discounts | **HIGH** |
| 7 | **ranges.cxx/h** | Range definitions | 11 | DISCOUNTGROUP queries | **HIGH** |
| 8 | **controlling.cxx/h** | Controlling | 50 | Control queries | **MEDIUM** |
| 9 | **verbundcheck.cxx/h** | Verbund validation | 16 | Validation queries | **MEDIUM** |
| 10 | **aasrv.cpp/h** | Main server | 37 | getOrderEntryParam | **MEDIUM** |
| 11 | **filialpartner.cxx/h** | Branch partner | 42 | Partner queries | **MEDIUM** |
| 12 | **deliveryadvicelinediscounts.h** | Delivery advice | 27 | Discount line items | **LOW** |

**Example SQL in artikel.cxx (CRITICAL - 235 BranchNo refs):**
```sql
SELECT discount.BranchNo, discount.ArticleNo, discount.DiscountPct
FROM discount, customerpharmacygr, discountgrpmem
WHERE discount.BranchNo = :d->BRANCHNO                    -- CHANGE TO: = 0
  AND discount.BranchNo = customerpharmacygr.BranchNo     -- CHANGE TO: = 0
  AND discount.BranchNo = discountgrpmem.branchno         -- CHANGE TO: = 0
  AND discount.ArticleNo = :articleNo
  ...
```

**Example SQL in customer.cxx (CRITICAL - 172 BranchNo refs):**
```sql
SELECT discountgrp.BranchNo, discountgrp.DiscountGrpNo, ...
FROM discountgrp, discountgrpmem
WHERE DiscountGrp.BranchNo = :d->BRANCHNO                 -- CHANGE TO: = 0
  AND DiscountGrp.BranchNo = DiscountGrpMem.BranchNo      -- CHANGE TO: = 0
  AND DiscountGrp.CustomerNo = :customerNo
  ...
```

#### 3.2.4 libcsc/customer Library

| # | Module | Files | Description | BranchNo Usage | Priority |
|---|--------|-------|-------------|----------------|----------|
| 1 | **discountaccount/** | 11 files | Discount account management | `WHERE branchno=` in SQL | **CRITICAL** |
| 2 | **pricesanddiscounts/** | 13 files | Price & discount queries | `WHERE filialnr=` (branch) | **CRITICAL** |
| 3 | **promotions/** | 13 files | Promotion management | Branch filtering | **HIGH** |
| 4 | **customercondition/** | 11 files | Customer conditions | Discount condition queries | **HIGH** |
| 5 | **paymentconditions/** | 11 files | Payment conditions | Payment discount terms | **MEDIUM** |
| 6 | **payments/** | 13 files | Payment processing | Payment with branch | **MEDIUM** |
| 7 | **customerrepository.cpp/h** | 2 files | Customer repository | Discount references | **MEDIUM** |

**Example SQL (discountaccountsql.cpp):**
```cpp
sql << "SELECT * FROM cstdiscountcont "
    << "WHERE branchno=" << branchno          -- CHANGE TO: branchno=0
    << " AND customerno=" << customerno;
```

**Example SQL (pricesanddiscountssql.cpp):**
```cpp
sql << "SELECT * FROM discount "
    << "WHERE filialnr=" << branchno          -- CHANGE TO: filialnr=0
    << " AND idfnr=" << customerno;
```

#### 3.2.5 Database Access Layer (pxdb)

**Cursor Definitions (pxdbxx.h):**
```cpp
// All cursors include BranchNo as first filter
cCRSDISCOUNT_BRARTMAN_0    = 1024,      // Branchno + Article (manufacturer)
cCRSDISCOUNT_BRSINGLEART_0 = 2048,      // Branchno + Article (single)
cCRSDISCOUNT_BRSINGLEART_1 = 4096,      // Branchno + Article variant
cCRSDISCOUNT_BROCCASIONS   = 8192,      // Branchno + Article (occasions)
cCRSDISCOUNT_BRARTMAN_1    = 1048576,   // Branchno + Article (manufacturer)
cCRSDISCOUNT_BRCUSTGRP_0   = 16777216   // Branchno + Customer + PharmGroup
```

**Primary Key Macros (keys.h):**
```cpp
#define PKtdiscount       BRANCHNO = :recordp->BRANCHNO ...
#define DWtdiscount       where BRANCHNO = :recordp->BRANCHNO ...
#define PKtdiscountgrp    BRANCHNO = :recordp->BRANCHNO ...
#define PKtdiscountgrpmem BRANCHNO = :recordp->BRANCHNO ...
#define PKtcstdiscountcont BRANCHNO = :recordp->BRANCHNO ...
```

**Database Table Access (tdiscount.cxx - CRITICAL):**
```cpp
// Cursor C2 - Select discount by article
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = :recordp->BRANCHNO        -- CHANGE TO: = 0
    AND ARTICLENO = :recordp->ARTICLENO;

// Cursor C3 - Select by customer
EXEC SQL DECLARE C3 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = :recordp->BRANCHNO        -- CHANGE TO: = 0
    AND CUSTOMERNO = :recordp->CUSTOMERNO;

// Cursor C4, C5, C6, C7 - All similar patterns
// TOTAL: 7 cursors to modify
```

---

## 4. Layer-by-Layer Analysis

### 4.1 Architecture Overview

The system follows a **4-layer architecture**:

```
┌─────────────────────────────────────────────────────────┐
│  LAYER 1: DATA INGESTION (Overnight Batch)             │
│  Package: pharmos.outbound.csc_load                     │
│  Purpose: Load discount data from ZDP to KSC database  │
├─────────────────────────────────────────────────────────┤
│  • Shell Scripts (loadconditions.sh × 6 countries)     │
│  • Batch Programs (loadconditions.cxx, loadpricelist.cxx)|
│  • Writes to: DISCOUNT, DISCOUNTGRP, DISCOUNTGRPMEM    │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  LAYER 2: DATABASE ACCESS (SQL Cursors)                │
│  Package: pxdb library                                  │
│  Purpose: Abstract database operations                 │
├─────────────────────────────────────────────────────────┤
│  • Cursor Definitions (tdiscount.cxx, tcstdiscacc.cxx) │
│  • Embedded SQL (EXEC SQL ... WHERE BRANCHNO = ?)      │
│  • Reads from: All discount tables                     │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  LAYER 3: BUSINESS LOGIC (Core Processing)             │
│  Packages: pxverbund, aapserv, libcsc                  │
│  Purpose: Implement discount calculation logic         │
├─────────────────────────────────────────────────────────┤
│  • pxverbund: Core discount calculation engine         │
│  • aapserv: Application server with business rules     │
│  • libcsc: Customer-specific discount management       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  LAYER 4: API LAYER (External Interface)               │
│  Package: thrift service handlers                       │
│  Purpose: Expose discount services via Apache Thrift   │
├─────────────────────────────────────────────────────────┤
│  • Thrift Handlers (customerhandler, orderhandler)     │
│  • IDL Definitions (csccustomer.thrift, cscorder.thrift)|
│  • Exposes: getPricesAndDiscounts, getDiscountAccount  │
└─────────────────────────────────────────────────────────┘
```

### 4.2 Layer 1: Data Ingestion (CSC_LOAD)

**Orchestration of Changes:**

```
STEP 1: Fix Shell Scripts (6 countries)
├── Action: Remove Branch 0 rejection at line ~220
├── Files: loadconditions.sh (AT, CH, BG, HR, FR, RS)
├── Effort: 1 day
└── Testing: Test with -vz 0 parameter

STEP 2: Modify C++ Batch Loaders
├── Action: Change INSERT/UPDATE to use BRANCHNO=0
├── Files: loadconditions.cxx (primary), loadpricelist.cxx, loadrange.cxx
├── Effort: 2 days
└── Testing: Unit tests for database operations

STEP 3: Update APX Job Scheduler
├── Action: Replace 20 jobs with 1 job (Branch 0)
├── Configuration: APX scheduler in dev/qa/prod environments
├── Effort: 1 day
└── Testing: Job execution and completion monitoring
```

**Key Code Change (loadconditions.cxx):**
```cpp
// BEFORE: Variable branch insertion
short sBranchno = atoi(argv[i]);  // Gets branch 1-20 from parameter
exec sql insert into discount (branchno, articleno, ...)
    values (:sBranchno, :articleNo, ...);

// AFTER: Fixed Branch 0 insertion
short sBranchno = 0;  // Fixed to Branch 0 for country-level
exec sql insert into discount (branchno, articleno, ...)
    values (0, :articleNo, ...);  // Hardcoded 0 for centralized data
```

### 4.3 Layer 2: Database Access (PXDB)

**Orchestration of Changes:**

```
STEP 4: Update SQL Cursors
├── Action: Change WHERE BRANCHNO = :var to WHERE BRANCHNO = 0
├── Files: tdiscount.cxx (7 cursors), tcstdiscacc.cxx
├── Affected Cursors:
│   ├── C2: SELECT by Article
│   ├── C3: SELECT by Customer
│   ├── C4: SELECT by Discount Group
│   ├── C5: SELECT by Pharmacy Group
│   ├── C6: SELECT by Manufacturer
│   └── C7: SELECT by Date Range
├── Effort: 1 day
└── Testing: Cursor query validation
```

**Example Cursor Modification:**
```cpp
// BEFORE: Dynamic branch selection
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = :recordp->BRANCHNO  // Variable branch
    AND ARTICLENO = :recordp->ARTICLENO;

// AFTER: Fixed Branch 0 selection
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = 0                    // Fixed to Branch 0
    AND ARTICLENO = :recordp->ARTICLENO;
```

### 4.4 Layer 3: Business Logic

**Orchestration by Sub-Layer:**

```
STEP 5a: Update pxverbund Core (12 modules)
├── Priority: CRITICAL
├── Action: Pass BranchNo=0 to all Select methods
├── Key Files:
│   ├── discount.cpp: 10+ Select methods
│   ├── calcdiscount.cpp: Discount calculation cascade
│   ├── artdiscountinfo.cpp: Article discount
│   └── ordcstdiscacc.cpp: Customer discount account
├── Effort: 5 days
└── Testing: Discount calculation validation

STEP 5b: Update aapserv Server (24 files)
├── Priority: CRITICAL
├── Action: Modify SQL WHERE clauses to use BRANCHNO=0
├── Key Files:
│   ├── artikel.cxx: 235 BranchNo references, 6+ SQL queries
│   ├── customer.cxx: 172 BranchNo references, 4+ SQL queries
│   ├── promo.cxx: 37 BranchNo references
│   └── orders.cxx: 39 BranchNo references
├── Effort: 5 days
└── Testing: Application server integration tests

STEP 5c: Update libcsc Customer Library (74 files)
├── Priority: HIGH
├── Action: Modify SQL in discountaccount and pricesanddiscounts
├── Modules:
│   ├── discountaccount/ (11 files): WHERE branchno=0
│   ├── pricesanddiscounts/ (13 files): WHERE filialnr=0
│   ├── promotions/ (13 files): Branch filtering
│   └── customercondition/ (11 files): Condition queries
├── Effort: 3 days
└── Testing: Customer-specific discount scenarios
```

**Example Method Signature Changes (discount.cpp):**
```cpp
// BEFORE: BranchNo as parameter
int pxDiscountList::Select(const short BranchNo, long ArticleNo) {
    // Query with variable BranchNo
    sql = "SELECT * FROM DISCOUNT WHERE BRANCHNO = ? AND ARTICLENO = ?";
    executeQuery(sql, BranchNo, ArticleNo);
}

// AFTER: Remove BranchNo parameter (implicitly use 0)
int pxDiscountList::Select(long ArticleNo) {
    // Query with fixed BranchNo=0
    sql = "SELECT * FROM DISCOUNT WHERE BRANCHNO = 0 AND ARTICLENO = ?";
    executeQuery(sql, ArticleNo);
}
```

### 4.5 Layer 4: API Layer (THRIFT)

**Orchestration of Changes:**

```
STEP 6: Update Thrift Service Handlers
├── Action: Pass BranchNo=0 to pxverbund/aapserv calls
├── Files:
│   ├── customerhandler.cpp (38 refs): getPricesAndDiscounts
│   ├── orderhandler.cpp (16 refs): Order discount processing
│   ├── inquiryhandler.cpp (4 refs): Inquiry methods
│   └── callbackhandler.cpp (18 refs): Callback with discounts
├── Effort: 3 days
└── Testing: API endpoint integration tests

STEP 7: Review Thrift IDL Contracts (Optional)
├── Action: Update documentation to reflect Branch 0 usage
├── Files: csccustomer.thrift, cscorder.thrift (14 total IDL files)
├── Effort: 1 day
└── Note: IDL changes NOT required if BranchNo removed from API
```

**Example Handler Modification:**
```cpp
// customerhandler.cpp - getPricesAndDiscounts method

// BEFORE: Pass current branch from request
PricesAndDiscountsResponse 
    CustomerHandler::getPricesAndDiscounts(const PricesAndDiscountsRequest& request) {
    
    short branchNo = request.branchNo;  // From client request
    
    // Call core logic with branch from request
    discountList.Select(branchNo, request.articleNo);
    ...
}

// AFTER: Always use Branch 0
PricesAndDiscountsResponse 
    CustomerHandler::getPricesAndDiscounts(const PricesAndDiscountsRequest& request) {
    
    short branchNo = 0;  // Fixed to Branch 0 for country-level
    
    // Call core logic with Branch 0
    discountList.Select(0, request.articleNo);  // Branch 0
    ...
}
```

---

## 5. Database Schema & Tables

### 5.1 Source Structure (ZDP Side)

**Table: ZDISCOUNT** (Source from Central Data Pool)

**Key Characteristic:** **NO BRANCHNO field** - data is already country-level

```c
struct N_ZDISCOUNT {
    // PRIMARY KEY
    long ARTICLENO;              // Article number (product ID)
    long DISCOUNTGRPNO;          // Discount group number
    char PHARMACYGROUPID[4];     // Pharmacy group ID
    long CUSTOMERNO;             // Customer number
    
    // DISCOUNT CONFIGURATION
    short GRPDISCOUNTTYP;        // Group discount type
    short DISCOUNTTYPE;          // Discount type (percentage, fixed, etc.)
    short DISCOUNTSPEC;          // Discount specification
    double DISCOUNTVALUEPCT;     // Discount value (percentage)
    double DISCOUNTQTYPCT;       // Discount quantity percentage
    double SURCHARGEPCT;         // Surcharge percentage
    double FIXEDPRICE;           // Fixed price
    double REFUNDPCT;            // Refund percentage
    
    // VALIDITY
    long DATEFROM;               // Valid from date (YYYYMMDD)
    long DATETO;                 // Valid to date (YYYYMMDD)
    
    // QUANTITIES
    long BASEQTY;                // Base quantity for discount
    short DISCOUNTQTY;           // Discount quantity
    
    // EXCLUSIONS
    char PHARMGRPEXCLUDED[4];    // Excluded pharmacy groups
    
    // FLAGS
    char INTERNALDISCOUNT[2];    // Internal discount flag
    long DISCOUNTARTICLE;        // Related discount article
    
    // ... 45+ total fields
};
```

**Storage:** ZDP database (ZDISCOUNT table)

**Data Volume:** ~100K-500K rows per country (depends on country size)

### 5.2 Target Structure (KSC Side)

**Table: LDDISCOUNT** (Local Discount in KSC)

**Key Difference:** **HAS BRANCHNO field** - added during load process

```c
struct N_LDDISCOUNT {
    // PRIMARY KEY
    short BRANCHNO;              // *** BRANCH NUMBER - ADDED FIELD ***
    long ARTICLENO;
    long DISCOUNTGRPNO;
    char PHARMACYGROUPID[4];
    long CUSTOMERNO;
    
    // DISCOUNT CONFIGURATION (same as ZDISCOUNT)
    short GRPDISCOUNTTYP;
    long DATEFROM;
    long DATETO;
    long BASEQTY;
    short DISCOUNTSPEC;
    short DISCOUNTTYPE;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    double DISCOUNTQTYPCT;
    double SURCHARGEPCT;
    char PHARMGRPEXCLUDED[4];
    double FIXEDPRICE;
    double REFUNDPCT;
    char INTERNALDISCOUNT[2];
    long DISCOUNTARTICLE;
    
    // ... same fields as ZDISCOUNT + BRANCHNO
};
```

**Storage:** KSC database (DISCOUNT table in Informix)

**Current Data Volume:** ~100K-500K rows **× 20 branches** = **2M-10M rows** (MASSIVE DUPLICATION!)

**After CPR:** ~100K-500K rows **× 1 branch (Branch 0)** = **100K-500K rows** (95% REDUCTION!)

### 5.3 All Impacted Database Tables

| # | Table Name | Has BRANCHNO | Indexes with BRANCHNO | Current Records | After CPR | Priority |
|---|------------|--------------|----------------------|-----------------|-----------|----------|
| 1 | **discount** | YES (PK) | 5 composite indexes | 2M-10M × 20 | 2M-10M × 1 | **CRITICAL** |
| 2 | **discountgrp** | YES (PK) | 2 composite indexes | 50K × 20 | 50K × 1 | **HIGH** |
| 3 | **discountgrpmem** | YES (PK) | 3 composite indexes | 200K × 20 | 200K × 1 | **HIGH** |
| 4 | **cstdiscountcont** | YES (PK) | 2 composite indexes | 100K × 20 | 100K × 1 | **HIGH** |
| 5 | **customerpharmacygr** | YES | 1 composite index | 50K × 20 | 50K × 1 | **MEDIUM** |
| 6 | **discountlist** | NO (ORDER_TYPE) | - | 10K | 10K | **REVIEW** |

**Total Storage Impact:**
- **Before CPR:** ~4.5M-20M discount-related records
- **After CPR:** ~450K-2M discount-related records  
- **Storage Reduction:** **~95%** (10-20 GB saved per country)

### 5.4 Database Indexes Affected

**From lddiscount.h:**
```sql
-- All indexes include BranchNo as FIRST column (most selective)

CREATE INDEX i_discount_1 ON discount(
    BranchNo,              -- Currently filters to 1/20th of data
    ArticleNo,
    DiscountType,
    PharmacyGroupId
);

CREATE INDEX i_discount_2 ON discount(
    BranchNo,              -- Currently filters to 1/20th of data
    DiscountGrpNo,
    PharmacyGroupId
);

CREATE INDEX i_discount_3 ON discount(
    BranchNo,              -- Currently filters to 1/20th of data
    ArticleNo,
    CustomerNo
);

CREATE INDEX i_discount_4 ON discount(
    BranchNo,              -- Currently filters to 1/20th of data
    CustomerNo,
    PharmacyGroupId,
    ArticleNo,
    ManufacturerNo,
    DiscountGrpNo
);

CREATE INDEX i_discount_5 ON discount(
    BranchNo,              -- Currently filters to 1/20th of data
    ManufacturerNo
);
```

**Index Optimization Considerations:**

**Before CPR:** `BranchNo` filters to **1/20th** of data (5% selectivity) - **EXCELLENT**

**After CPR:** `BranchNo=0` always matches **100%** of data - **NO SELECTIVITY!**

**Recommendation for Phase III (Future Optimization):**
1. **Option A:** Remove `BranchNo` from indexes entirely (requires schema change)
2. **Option B:** Keep indexes but accept reduced selectivity (easier, backward compatible)

**Decision:** For **Phase II**, keep indexes unchanged (Option B) to minimize risk. Consider Option A in Phase III.

---

## 6. Implementation Plan

### 6.1 Phased Approach Overview

```
┌────────────────────────────────────────────────────────┐
│  PHASE I: ENABLE BRANCH 0 LOADING (Week 1-2)          │
│  Goal: Allow discount data to be loaded to Branch 0   │
│  Status: Foundation                                    │
└────────────────────────────────────────────────────────┘
              ↓
┌────────────────────────────────────────────────────────┐
│  PHASE II: UPDATE APPLICATIONS (Week 3-6)             │
│  Goal: All apps read from Branch 0 instead of local   │
│  Status: Core Implementation                           │
└────────────────────────────────────────────────────────┘
              ↓
┌────────────────────────────────────────────────────────┐
│  PHASE III: ARCHITECTURAL CLEANUP (Week 7-12 - Future)│
│  Goal: Remove BranchNo from tables, modernize arch    │
│  Status: Future Enhancement (Optional)                 │
└────────────────────────────────────────────────────────┘
```

### 6.2 Phase I: Enable Branch 0 Loading (Week 1-2)

**Objective:** Fix the blocking issue and enable discount data to be loaded to Branch 0

#### Week 1: Shell Script Modifications

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Fix loadconditions.sh for AT, CH, BG | 3 scripts modified, tested |
| **Tue** | Fix loadconditions.sh for HR, FR, RS | 3 scripts modified, tested |
| **Wed** | Test Branch 0 execution in DEV | All 6 countries validated |
| **Thu** | Code review and testing | Peer review complete |
| **Fri** | Deploy to QA environment | QA deployment complete |

**Critical Fix (All 6 Scripts):**
```bash
# File: pharmos.outbound.csc_load_-_/dev/src/environment/{country}/ksc/load/proc/loadconditions.sh
# Line ~220

# BEFORE:
if [[ "$vz" == "" ]] || (( 1 != `check_numeric_parameter "$vz"` )) || [[ "$vz" == "0" ]]; then

# AFTER:
if [[ "$vz" == "" ]] || (( 1 != `check_numeric_parameter "$vz"` )); then
```

**Testing:**
```bash
# Test Branch 0 acceptance
./loadconditions.sh -start -vz 0
# Expected: SUCCESS (no error about Branch 0)

# Test invalid branch rejection (should still work)
./loadconditions.sh -start -vz abc
# Expected: ERROR (invalid parameter)

# Test empty branch rejection (should still work)
./loadconditions.sh -start -vz ""
# Expected: ERROR (missing parameter)
```

#### Week 2: C++ Loader Modifications

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Modify loadconditions.cxx for Branch 0 | Code updated, unit tests written |
| **Tue** | Modify loadpricelist.cxx, loadrange.cxx | Additional loaders updated |
| **Wed** | Create migration script for existing data | SQL script to copy Branch 1 → Branch 0 |
| **Thu** | Execute test data load in DEV | Branch 0 data loaded successfully |
| **Fri** | Validation and comparison | Data integrity verified |

**Key Code Changes:**

**loadconditions.cxx:**
```cpp
// Function: main()
short sBranchno = 0;

// Command line parameter handling
else if ( !strcmp( schalter, "-vz" ) ) {
    sBranchno = atoi(argv[i]);
    // Allow Branch 0 for country-level discount data
}

// SQL INSERT statement
exec sql insert into discount (
    branchno, articleno, discountgrpno, pharmacygroupid, ...
) values (
    :sBranchno,  // Will be 0 for country-level
    :articleno,
    :discountgrpno,
    :pharmacygroupid,
    ...
);
```

**Migration Script (migrate_to_branch0.sql):**
```sql
-- Copy existing Branch 1 data to Branch 0 as initial seed
-- This allows parallel testing before full cutover

BEGIN WORK;

-- Delete any existing Branch 0 data (if testing)
DELETE FROM discount WHERE branchno = 0;
DELETE FROM discountgrp WHERE branchno = 0;
DELETE FROM discountgrpmem WHERE branchno = 0;
DELETE FROM cstdiscountcont WHERE branchno = 0;

-- Copy Branch 1 data to Branch 0
INSERT INTO discount (branchno, articleno, discountgrpno, ...)
SELECT 0 AS branchno, articleno, discountgrpno, ...
FROM discount
WHERE branchno = 1;

INSERT INTO discountgrp (branchno, discountgrpno, ...)
SELECT 0 AS branchno, discountgrpno, ...
FROM discountgrp
WHERE branchno = 1;

INSERT INTO discountgrpmem (branchno, discountgrpno, articleno, ...)
SELECT 0 AS branchno, discountgrpno, articleno, ...
FROM discountgrpmem
WHERE branchno = 1;

INSERT INTO cstdiscountcont (branchno, customerno, ...)
SELECT 0 AS branchno, customerno, ...
FROM cstdiscountcont
WHERE branchno = 1;

COMMIT WORK;
```

**Validation Queries:**
```sql
-- Verify row counts match
SELECT 
    (SELECT COUNT(*) FROM discount WHERE branchno = 0) as branch_0_count,
    (SELECT COUNT(*) FROM discount WHERE branchno = 1) as branch_1_count,
    CASE 
        WHEN (SELECT COUNT(*) FROM discount WHERE branchno = 0) = 
             (SELECT COUNT(*) FROM discount WHERE branchno = 1)
        THEN 'MATCH' 
        ELSE 'MISMATCH' 
    END as status;

-- Verify discount values are identical
SELECT articleno, customerno, discounttype, discountvaluepct
FROM discount WHERE branchno = 0
MINUS
SELECT articleno, customerno, discounttype, discountvaluepct
FROM discount WHERE branchno = 1;
-- Expected: 0 rows (no differences)
```

**Phase I Success Criteria:**
- ✅ All 6 shell scripts accept `-vz 0` parameter
- ✅ loadconditions.cxx successfully inserts to Branch 0
- ✅ Branch 0 data matches Branch 1 data (validation queries pass)
- ✅ No data loss or corruption
- ✅ Process completes within expected time (<5 minutes)

### 6.3 Phase II: Update Applications (Week 3-6)

**Objective:** Modify all applications to read discount data from Branch 0

#### Week 3: Database Access Layer (PXDB)

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Modify tdiscount.cxx (Cursors C2, C3, C4) | 3 cursors updated |
| **Tue** | Modify tdiscount.cxx (Cursors C5, C6, C7) | 4 cursors updated |
| **Wed** | Modify tcstdiscacc.cxx cursors | Customer discount cursors updated |
| **Thu** | Update keys.h macros | Primary key macros reviewed |
| **Fri** | Unit testing and validation | All cursors tested |

**Cursor Modifications (tdiscount.cxx):**
```cpp
// BEFORE: Cursor C2
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = :recordp->BRANCHNO
    AND ARTICLENO = :recordp->ARTICLENO;

// AFTER: Cursor C2
EXEC SQL DECLARE C2 CURSOR FOR
    SELECT * FROM DISCOUNT
    WHERE BRANCHNO = 0  // Fixed to Branch 0
    AND ARTICLENO = :recordp->ARTICLENO;

// Apply same pattern to cursors C3, C4, C5, C6, C7
```

#### Week 4: Core Logic Layer (pxverbund)

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Modify discount.cpp Select methods (5 methods) | Methods 1-5 updated |
| **Tue** | Modify discount.cpp Select methods (remaining 5+) | All Select methods updated |
| **Wed** | Modify calcdiscount.cpp calculation cascade | Calculation logic updated |
| **Thu** | Modify artdiscountinfo.cpp, ordcstdiscacc.cpp | Supporting modules updated |
| **Fri** | Unit testing and integration testing | pxverbund tests pass |

**Method Signature Changes (discount.cpp):**
```cpp
// BEFORE: BranchNo as parameter
class pxDiscountList {
public:
    int Select(const short BranchNo, long ArticleNo);
    int Select(const short BranchNo, long ArticleNo, long CustomerNo);
    int Select(const short BranchNo, long ArticleNo, short DiscountType, ...);
    int SelectRange(const short BranchNo, long DiscountGrpNo, long CustomerNo);
    // ... 6+ more methods
};

// AFTER: Remove BranchNo parameter (or keep but ignore, always use 0)
class pxDiscountList {
public:
    int Select(long ArticleNo);  // BranchNo removed or fixed to 0 internally
    int Select(long ArticleNo, long CustomerNo);
    int Select(long ArticleNo, short DiscountType, ...);
    int SelectRange(long DiscountGrpNo, long CustomerNo);
    // ... 6+ more methods
};

// Implementation
int pxDiscountList::Select(long ArticleNo) {
    // Always use Branch 0
    return SelectInternal(0, ArticleNo);  // Branch 0 hardcoded
}
```

#### Week 5: Application Server (aapserv)

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Modify artikel.cxx SQL queries | 235 BranchNo refs updated |
| **Tue** | Modify customer.cxx SQL queries | 172 BranchNo refs updated |
| **Wed** | Modify promo.cxx, promoinfo.cxx | Promotion queries updated |
| **Thu** | Modify orders.cxx, callback.cxx, ranges.cxx | Order/callback queries updated |
| **Fri** | Integration testing | aapserv tests pass |

**SQL Modification Pattern (artikel.cxx):**
```sql
-- BEFORE:
SELECT discount.BranchNo, discount.ArticleNo, discount.DiscountPct
FROM discount, customerpharmacygr, discountgrpmem
WHERE discount.BranchNo = :d->BRANCHNO               -- Variable
  AND discount.BranchNo = customerpharmacygr.BranchNo
  AND discount.BranchNo = discountgrpmem.branchno
  AND discount.ArticleNo = :articleNo;

-- AFTER:
SELECT discount.BranchNo, discount.ArticleNo, discount.DiscountPct
FROM discount, customerpharmacygr, discountgrpmem
WHERE discount.BranchNo = 0                          -- Fixed to Branch 0
  AND discount.BranchNo = customerpharmacygr.BranchNo
  AND discount.BranchNo = discountgrpmem.branchno
  AND discount.ArticleNo = :articleNo;
```

#### Week 6: Customer Library & API Layer

| Day | Task | Deliverable |
|-----|------|-------------|
| **Mon** | Modify libcsc/discountaccount/* | 11 files updated |
| **Tue** | Modify libcsc/pricesanddiscounts/* | 13 files updated |
| **Wed** | Modify libcsc/promotions/*, customercondition/* | 24 files updated |
| **Thu** | Modify Thrift handlers (customerhandler, orderhandler) | API layer updated |
| **Fri** | End-to-end integration testing | Full system test pass |

**libcsc SQL Modification (discountaccountsql.cpp):**
```cpp
// BEFORE:
sql << "SELECT * FROM cstdiscountcont "
    << "WHERE branchno=" << branchno          // Variable
    << " AND customerno=" << customerno;

// AFTER:
sql << "SELECT * FROM cstdiscountcont "
    << "WHERE branchno=0"                     // Fixed to Branch 0
    << " AND customerno=" << customerno;
```

**Thrift Handler Modification (customerhandler.cpp):**
```cpp
// BEFORE:
PricesAndDiscountsResponse 
CustomerHandler::getPricesAndDiscounts(const PricesAndDiscountsRequest& request) {
    short branchNo = request.branchNo;  // From client
    
    // Pass client's branch to core logic
    pxDiscountList discounts;
    discounts.Select(branchNo, request.articleNo);
    ...
}

// AFTER:
PricesAndDiscountsResponse 
CustomerHandler::getPricesAndDiscounts(const PricesAndDiscountsRequest& request) {
    short branchNo = 0;  // Fixed to Branch 0
    
    // Always pass Branch 0 to core logic
    pxDiscountList discounts;
    discounts.Select(0, request.articleNo);  // Branch 0
    ...
}
```

**Phase II Success Criteria:**
- ✅ All 74 components modified and tested
- ✅ All branches (1-20) query from Branch 0
- ✅ Discount calculations identical to legacy system
- ✅ No performance regression (<= baseline response time)
- ✅ All regression tests pass (100%)
- ✅ UAT sign-off from business users

### 6.4 Phase III: Architectural Cleanup (Week 7-12 - Optional Future Enhancement)

**Objective:** Remove BranchNo from database schema and modernize architecture

**Note:** This phase is **OPTIONAL** and can be deferred to future releases. Phase I & II are sufficient for CPR go-live.

**Recommended Enhancements (from OUTPUT02 analysis):**

#### New Database Tables

**1. country_discount_rules** (Country-Specific Business Rules)
```sql
CREATE TABLE country_discount_rules (
    country_code CHAR(2) NOT NULL,          -- DE, AT, CH, FR, BG, HR, RS
    discount_type INT NOT NULL,
    min_discount_pct DECIMAL(5,2),
    max_discount_pct DECIMAL(5,2) NOT NULL,
    min_margin_pct DECIMAL(5,2) NOT NULL,   -- Minimum profit margin
    stackable CHAR(1) DEFAULT 'N',          -- Can combine with other discounts?
    requires_approval CHAR(1) DEFAULT 'N',
    status VARCHAR(20) DEFAULT 'ACTIVE',
    effective_date DATE NOT NULL,
    expiry_date DATE,
    created_by VARCHAR(50),
    created_at DATETIME YEAR TO SECOND DEFAULT CURRENT YEAR TO SECOND,
    PRIMARY KEY (country_code, discount_type, effective_date)
);

-- Example data:
INSERT INTO country_discount_rules VALUES
    ('CH', 1, 0, 15.00, 18.00, 'N', 'Y', 'ACTIVE', '2025-01-01', NULL, 'SYSTEM', CURRENT),
    ('AT', 1, 0, 20.00, 15.00, 'N', 'Y', 'ACTIVE', '2025-01-01', NULL, 'SYSTEM', CURRENT),
    ('DE', 1, 0, 25.00, 12.00, 'Y', 'N', 'ACTIVE', '2025-01-01', NULL, 'SYSTEM', CURRENT);
```

**2. discount_precedence_rules** (Conflict Resolution)
```sql
CREATE TABLE discount_precedence_rules (
    rule_id INT NOT NULL AUTO_INCREMENT,
    country_code CHAR(2) NOT NULL,
    rule_priority INT NOT NULL,             -- Lower number = higher priority
    discount_type_1 INT,
    discount_type_2 INT,
    discount_type_3 INT,
    action VARCHAR(20) NOT NULL,            -- 'HIGHEST', 'LOWEST', 'SUM', 'FIRST'
    max_combined_discount DECIMAL(5,2),
    status VARCHAR(20) DEFAULT 'ACTIVE',
    effective_date DATE NOT NULL,
    expiry_date DATE,
    PRIMARY KEY (rule_id)
);

-- Example: When multiple discounts apply, take highest
INSERT INTO discount_precedence_rules VALUES
    (1, 'DE', 1, 1, 2, 3, 'HIGHEST', 25.00, 'ACTIVE', '2025-01-01', NULL);
```

**3. payment_term_discount_config** (Payment Discount Matrix)
```sql
CREATE TABLE payment_term_discount_config (
    config_id INT NOT NULL AUTO_INCREMENT,
    country_code CHAR(2) NOT NULL,
    payment_days INT16 NOT NULL,           -- e.g., 10, 30, 60 days
    discount_pct DECIMAL(5,2),
    discount_amount DECIMAL(10,2),
    min_order_value DECIMAL(10,2),
    status VARCHAR(20) DEFAULT 'ACTIVE',
    effective_date DATE NOT NULL,
    expiry_date DATE,
    PRIMARY KEY (config_id)
);

-- Example: 2% discount for payment within 10 days
INSERT INTO payment_term_discount_config VALUES
    (1, 'DE', 10, 2.00, NULL, 0, 'ACTIVE', '2025-01-01', NULL),
    (2, 'DE', 30, 0, NULL, 0, 'ACTIVE', '2025-01-01', NULL);
```

#### New Service Classes

**DiscountValidationService** (TypeScript)
```typescript
class DiscountValidationService {
    validateDiscount(discount: Discount, country: string): ValidationResult {
        // Load country-specific rules
        const countryRules = this.getCountryRules(country);
        
        // Check maximum discount percentage
        if (discount.percentage > countryRules.maxDiscountPct) {
            return { 
                valid: false, 
                reason: `Exceeds country maximum: ${countryRules.maxDiscountPct}%` 
            };
        }
        
        // Check minimum margin protection
        const margin = this.calculateMargin(discount);
        if (margin < countryRules.minMarginPct) {
            return { 
                valid: false, 
                reason: `Violates minimum margin: ${countryRules.minMarginPct}%` 
            };
        }
        
        // Check approval requirements
        if (countryRules.requiresApproval && !discount.approvedBy) {
            return { 
                valid: false, 
                reason: "Requires management approval" 
            };
        }
        
        return { valid: true };
    }
}
```

**Phase III Success Criteria:**
- ✅ New tables created and populated
- ✅ Services implemented and tested
- ✅ Country-specific rules enforced
- ✅ API endpoints functional
- ✅ Documentation updated
- ✅ Zero regression from Phase II

---

## 7. Risk Assessment & Mitigation

### 7.1 Risk Matrix

| # | Risk | Probability | Impact | Severity | Mitigation |
|---|------|-------------|--------|----------|------------|
| 1 | **Regression in discount calculation** | Medium | Critical | **HIGH** | Parallel running, extensive testing, automated validation |
| 2 | **Data loss during migration** | Low | Critical | **MEDIUM** | Full backup, rollback plan, parallel data validation |
| 3 | **Performance degradation** | Low | High | **MEDIUM** | Index optimization, benchmarking, performance monitoring |
| 4 | **Shell script rejection of Branch 0** | High (before fix) | Critical | **CRITICAL** | **FIXED in Phase I - highest priority** |
| 5 | **SQL cursor query failures** | Medium | High | **HIGH** | Thorough testing, error logging, rollback procedures |
| 6 | **APX job configuration errors** | Medium | High | **HIGH** | Test in DEV/QA first, staged deployment |
| 7 | **Branch-specific data requirements discovered late** | Low | High | **MEDIUM** | Comprehensive requirements review, stakeholder validation |
| 8 | **GxP compliance gaps** | Low | Critical | **MEDIUM** | Early compliance review, validation documentation |
| 9 | **Incomplete file identification** | Low | Medium | **LOW** | 4-developer analysis review, source code grep validation |
| 10 | **Integration issues between layers** | Medium | High | **HIGH** | Layer-by-layer integration testing, end-to-end testing |

### 7.2 Detailed Mitigation Strategies

#### Risk #1: Regression in Discount Calculation

**Mitigation Strategy:**
1. **Parallel Running Period (2 weeks)**
   - Load discount data to BOTH Branch 0 AND Branch 1-20 simultaneously
   - Run applications in "dual mode" - query both sources
   - Compare results for 100% accuracy

2. **Automated Validation Framework**
   ```sql
   -- Create validation table
   CREATE TABLE discount_validation_log (
       validation_id INT AUTO_INCREMENT,
       test_case_id INT,
       article_no LONG,
       customer_no LONG,
       branch_legacy SHORT,           -- Expected from Branch 1-20
       branch_zero SHORT,              -- Actual from Branch 0
       discount_pct_legacy DECIMAL(5,2),
       discount_pct_zero DECIMAL(5,2),
       match_status CHAR(1),           -- 'M'=Match, 'D'=Difference
       difference_pct DECIMAL(5,2),
       test_timestamp DATETIME,
       PRIMARY KEY (validation_id)
   );
   
   -- Validation query (run nightly)
   INSERT INTO discount_validation_log
   SELECT 
       NULL as validation_id,
       test_case_id,
       article_no,
       customer_no,
       d1.branchno as branch_legacy,
       d0.branchno as branch_zero,
       d1.discountvaluepct as discount_pct_legacy,
       d0.discountvaluepct as discount_pct_zero,
       CASE 
           WHEN d1.discountvaluepct = d0.discountvaluepct THEN 'M'
           ELSE 'D'
       END as match_status,
       ABS(d1.discountvaluepct - d0.discountvaluepct) as difference_pct,
       CURRENT
   FROM discount d1
   INNER JOIN discount d0 
       ON d1.articleno = d0.articleno
       AND d1.customerno = d0.customerno
       AND d1.discounttype = d0.discounttype
   WHERE d1.branchno = 1   -- Legacy Branch 1
     AND d0.branchno = 0   -- New Branch 0
     AND d1.discountvaluepct != d0.discountvaluepct;  -- Differences only
   ```

3. **Business User Acceptance Testing (UAT)**
   - Select 100 representative test cases per country
   - Business users manually verify discount calculations
   - Sign-off required before production deployment

#### Risk #2: Data Loss During Migration

**Mitigation Strategy:**
1. **Full Database Backup Before Migration**
   ```bash
   # Backup all discount tables
   dbexport ksc_database -t discount -t discountgrp -t discountgrpmem -t cstdiscountcont
   # Expected: ~10-20 GB backup file
   # Storage: Secure backup server with 30-day retention
   ```

2. **Incremental Backup During Migration**
   ```bash
   # Backup every hour during migration window
   while migration_in_progress; do
       dbexport ksc_database -t discount --incremental
       sleep 3600  # 1 hour
   done
   ```

3. **Rollback Script Ready**
   ```sql
   -- Rollback procedure (restore from backup)
   BEGIN WORK;
   
   -- Drop Branch 0 data
   DELETE FROM discount WHERE branchno = 0;
   DELETE FROM discountgrp WHERE branchno = 0;
   DELETE FROM discountgrpmem WHERE branchno = 0;
   DELETE FROM cstdiscountcont WHERE branchno = 0;
   
   -- Re-enable Branch 1-20 jobs
   -- (via APX scheduler)
   
   COMMIT WORK;
   
   -- Import backup data if needed
   dbimport ksc_database < discount_backup_20251230.sql
   ```

#### Risk #3: Performance Degradation

**Mitigation Strategy:**
1. **Baseline Performance Metrics (Before CPR)**
   ```sql
   -- Capture current performance
   SELECT 
       'discount' as table_name,
       COUNT(*) as row_count,
       AVG(DBINFO('sqlca.sqlerrd1')) as avg_query_time_ms
   FROM discount
   WHERE branchno BETWEEN 1 AND 20;
   
   -- Sample query performance (current)
   SET EXPLAIN ON;
   SELECT * FROM discount 
   WHERE branchno = 1 AND articleno = 12345;
   SET EXPLAIN OFF;
   -- Expected: <10ms with index i_discount_1
   ```

2. **Target Performance Metrics (After CPR)**
   ```sql
   -- Target: No regression (same or better performance)
   SELECT * FROM discount 
   WHERE branchno = 0 AND articleno = 12345;
   -- Expected: <10ms (same or better than baseline)
   ```

3. **Performance Monitoring Dashboard**
   - Real-time query latency tracking
   - Overnight batch execution time (target: 95% reduction)
   - Database storage utilization (target: 95% reduction)
   - Alerting for queries >20ms (2x baseline)

4. **Index Optimization (If Needed)**
   ```sql
   -- If performance degrades, consider:
   -- Option A: Keep current indexes (accept reduced selectivity)
   -- Option B: Drop BranchNo from indexes (Phase III)
   
   -- Monitor index usage
   SELECT 
       tabname,
       idxname,
       nkeys,
       cluster,
       seqscans,
       idxscans
   FROM sysmaster:sysindexes
   WHERE tabname = 'discount';
   ```

#### Risk #4: Shell Script Rejection of Branch 0

**Mitigation Strategy:**
✅ **HIGHEST PRIORITY - Fixed in Phase I Week 1**

1. **Root Cause:** Line 220 in loadconditions.sh explicitly blocks Branch 0
2. **Fix:** Remove `|| [[ "$vz" == "0" ]]` condition
3. **Validation:** Test with `-vz 0` parameter in DEV before QA/PROD
4. **Deployment:** All 6 country variants must be updated together

---

## 8. Testing Strategy

### 8.1 Testing Pyramid

```
         ┌──────────────────────────┐
         │  UAT (Business Users)    │  ← 100 test cases
         │  Manual discount validation│
         └──────────────────────────┘
                    ▲
         ┌──────────────────────────┐
         │  Integration Tests       │  ← 50 test scenarios
         │  End-to-end workflows    │
         └──────────────────────────┘
                    ▲
         ┌──────────────────────────┐
         │  Component Tests         │  ← 200 test cases
         │  API, Service, SQL layer │
         └──────────────────────────┘
                    ▲
         ┌──────────────────────────┐
         │  Unit Tests              │  ← 500+ test cases
         │  Individual methods/functions│
         └──────────────────────────┘
```

### 8.2 Unit Tests (Layer 1 & 2)

**Scope:** Test individual methods and SQL queries

| Component | Test Cases | Coverage |
|-----------|------------|----------|
| loadconditions.cxx | 20 tests | INSERT, UPDATE, parameter validation |
| tdiscount.cxx cursors | 35 tests (5 per cursor × 7 cursors) | SELECT operations |
| discount.cpp methods | 60 tests (6 per method × 10 methods) | Discount selection logic |
| SQL queries (aapserv) | 100 tests | All WHERE BRANCHNO clauses |
| libcsc modules | 50 tests | Customer discount queries |
| **Total Unit Tests** | **265+** | **>80% code coverage** |

**Example Unit Test (discount.cpp):**
```cpp
// Test: Select by Article Number
TEST_F(DiscountTest, SelectByArticleNumber_Branch0) {
    // Arrange
    long articleNo = 12345;
    pxDiscountList discounts;
    
    // Act
    int result = discounts.Select(articleNo);
    
    // Assert
    ASSERT_EQ(result, 0);  // Success
    ASSERT_GT(discounts.Count(), 0);  // Found discounts
    
    // Verify all returned discounts have BranchNo=0
    for (int i = 0; i < discounts.Count(); i++) {
        ASSERT_EQ(discounts[i].BRANCHNO, 0);
    }
}
```

### 8.3 Integration Tests (Layer 3 & 4)

**Scope:** Test interactions between components

| Test Scenario | Description | Expected Result |
|---------------|-------------|-----------------|
| **End-to-End Order Flow** | Create order with discounts | Discount applied correctly from Branch 0 |
| **Customer Discount Query** | Get customer-specific discounts | Returns Branch 0 data |
| **Promotion Application** | Apply promotional discount | Stacks correctly with other discounts |
| **Payment Term Discount** | Calculate early payment discount | Correct percentage applied |
| **Multi-Branch Consistency** | Query from Branch 1, 5, 10, 20 | All return same Branch 0 data |
| **Date Range Validation** | Query discounts for date range | Only active discounts returned |
| **Discount Group** | Apply group discount to multiple items | All items get correct discount |
| **Pharmacy Group Exclusion** | Exclude pharmacy group from discount | Exclusion rules enforced |
| **Thrift API Integration** | Call getPricesAndDiscounts API | Returns correct Branch 0 discounts |
| **Batch Load Integration** | Run loadconditions for Branch 0 | Data loaded successfully |

**Example Integration Test:**
```cpp
// Test: End-to-End Order with Discount
TEST_F(IntegrationTest, OrderWithDiscount_UsesBranch0) {
    // Arrange
    Order order;
    order.customerNo = 9999;
    order.branchNo = 5;  // Customer at Branch 5
    
    OrderItem item;
    item.articleNo = 12345;
    item.quantity = 10;
    order.addItem(item);
    
    // Act
    OrderHandler handler;
    OrderResponse response = handler.calculatePrices(order);
    
    // Assert
    ASSERT_EQ(response.status, "SUCCESS");
    ASSERT_GT(response.totalDiscount, 0);  // Discount applied
    
    // Verify discount came from Branch 0
    DiscountDetail discount = response.items[0].discount;
    ASSERT_EQ(discount.sourceBranch, 0);  // Branch 0
}
```

### 8.4 Regression Tests

**Scope:** Ensure no existing functionality is broken

**Test Data Set:** 1,000 historical orders from production

```sql
-- Create test data table
CREATE TABLE regression_test_cases (
    test_id INT AUTO_INCREMENT,
    order_id LONG,
    article_no LONG,
    customer_no LONG,
    branch_no SHORT,
    order_date DATE,
    expected_discount_pct DECIMAL(5,2),
    expected_total_amount DECIMAL(10,2),
    test_status CHAR(1),  -- 'P'=Passed, 'F'=Failed, 'N'=Not Run
    actual_discount_pct DECIMAL(5,2),
    actual_total_amount DECIMAL(10,2),
    difference_pct DECIMAL(5,2),
    PRIMARY KEY (test_id)
);

-- Populate test cases from production history
INSERT INTO regression_test_cases
SELECT 
    NULL as test_id,
    order_id,
    article_no,
    customer_no,
    branch_no,
    order_date,
    discount_pct as expected_discount_pct,
    total_amount as expected_total_amount,
    'N' as test_status,
    NULL as actual_discount_pct,
    NULL as actual_total_amount,
    NULL as difference_pct
FROM order_history
WHERE order_date BETWEEN '2024-01-01' AND '2024-12-31'
ORDER BY RANDOM()
LIMIT 1000;
```

**Regression Test Execution:**
```bash
#!/bin/bash
# run_regression_tests.sh

echo "Running 1,000 regression tests..."

passed=0
failed=0

while read -r test_id article_no customer_no; do
    # Execute discount query with Branch 0
    result=$(./query_discount --branch 0 --article $article_no --customer $customer_no)
    
    # Compare with expected result
    if [ "$result" == "$expected" ]; then
        ((passed++))
        update_test_status $test_id 'P'
    else
        ((failed++))
        update_test_status $test_id 'F'
        log_failure $test_id "$result" "$expected"
    fi
done < regression_test_cases.csv

echo "Regression tests completed: $passed passed, $failed failed"

if [ $failed -eq 0 ]; then
    echo "✅ All regression tests PASSED"
    exit 0
else
    echo "❌ $failed regression tests FAILED"
    exit 1
fi
```

**Success Criteria:**
- ✅ **100% regression tests pass** (all 1,000 test cases)
- ✅ Zero financial discrepancies (discount amounts match exactly)
- ✅ Performance within acceptable range (<= 110% of baseline)

### 8.5 Performance Tests

**Scope:** Validate performance improvements and no degradation

| Metric | Baseline (Before) | Target (After) | Measurement |
|--------|-------------------|----------------|-------------|
| **Overnight Batch Duration** | 120 minutes × 20 jobs | 6 minutes × 1 job | APX job logs |
| **Database Storage** | 20 GB × 20 branches | 20 GB × 1 branch | Table statistics |
| **Discount Query Latency** | <10 ms (p50), <50 ms (p99) | <10 ms (p50), <50 ms (p99) | Application logs |
| **Order Processing Time** | <500 ms per order | <500 ms per order | End-to-end trace |
| **Concurrent Users** | 1,000 users | 1,000 users | Load testing |

**Performance Test Script:**
```bash
#!/bin/bash
# performance_test.sh

echo "Performance Test - Discount Query Latency"

iterations=10000
total_time=0

for i in $(seq 1 $iterations); do
    # Random article and customer
    article=$((RANDOM % 100000 + 1))
    customer=$((RANDOM % 50000 + 1))
    
    # Measure query time
    start=$(date +%s%N)
    ./query_discount --branch 0 --article $article --customer $customer > /dev/null
    end=$(date +%s%N)
    
    elapsed=$(((end - start) / 1000000))  # Convert to milliseconds
    total_time=$((total_time + elapsed))
done

avg_time=$((total_time / iterations))

echo "Average query time: ${avg_time}ms"

if [ $avg_time -le 10 ]; then
    echo "✅ Performance target met (p50 <10ms)"
    exit 0
else
    echo "❌ Performance target missed (p50 = ${avg_time}ms)"
    exit 1
fi
```

### 8.6 UAT (User Acceptance Testing)

**Scope:** Business users validate discount calculations in real-world scenarios

**Test Matrix (8 Countries × 12 Scenarios = 96 Test Cases):**

| Country | Scenario | Test Case | Expected Result |
|---------|----------|-----------|-----------------|
| **DE** | Article-specific discount | Article 12345 for Pharmacy Group A | 15% discount |
| **DE** | Customer-specific discount | Customer 9999 orders any article | 10% discount |
| **DE** | Promotional discount | Promo XYZ active until 2025-12-31 | 20% discount |
| **DE** | Discount stacking | Article + Customer + Promo | Highest discount (20%) |
| **DE** | Payment term discount | Payment within 10 days | Additional 2% |
| **DE** | Volume discount | Order quantity >= 100 units | 5% extra |
| **DE** | Pharmacy group exclusion | Excluded group tries to use discount | No discount |
| **DE** | Date range validation | Discount expired yesterday | No discount |
| **DE** | Minimum order value | Order total < minimum | No discount |
| **DE** | Multi-branch consistency | Same order from Branch 1, 5, 10, 20 | Identical discount |
| **DE** | Order modification | Add item to existing order | Discount recalculated |
| **DE** | Narcotics tracking (NTTD) | Order with narcotics | Special handling |
| **AT** | (Repeat 12 scenarios for Austria) | | |
| **CH** | (Repeat 12 scenarios for Switzerland) | | |
| **FR** | (Repeat 12 scenarios for France) | | |
| **BG** | (Repeat 12 scenarios for Bulgaria) | | |
| **HR** | (Repeat 12 scenarios for Croatia) | | |
| **RS** | (Repeat 12 scenarios for Serbia) | | |
| **Regional** | (Repeat 12 scenarios for Regional) | | |

**UAT Sign-Off Form:**
```
┌────────────────────────────────────────────────────┐
│      USER ACCEPTANCE TESTING SIGN-OFF              │
├────────────────────────────────────────────────────┤
│ Country: _______________________                   │
│ Test Date: _____________________                   │
│ Tester Name: ____________________                  │
│                                                    │
│ Test Results:                                      │
│   [ ] All 12 scenarios passed                      │
│   [ ] ______ scenarios failed (list below)         │
│                                                    │
│ Failed Scenarios:                                  │
│ _____________________________________________     │
│ _____________________________________________     │
│                                                    │
│ Comments:                                          │
│ _____________________________________________     │
│ _____________________________________________     │
│                                                    │
│ Approval:                                          │
│   [ ] Approved for production deployment           │
│   [ ] Requires fixes before approval               │
│                                                    │
│ Signature: _________________ Date: __________     │
└────────────────────────────────────────────────────┘
```

**Success Criteria:**
- ✅ **All 96 UAT test cases pass** (100% pass rate)
- ✅ **Sign-off from all 8 countries** (business approval)
- ✅ Zero financial discrepancies reported by users
- ✅ User satisfaction rating >= 4.0/5.0

---

## 9. Deployment Plan

### 9.1 Deployment Strategy

**Approach:** **Phased Rollout with Pilot Country**

```
┌────────────────────────────────────────────────────┐
│  WEEK 7: BULGARIA PILOT (Low Volume)              │
│  - Deploy to BG production environment             │
│  - 24-hour monitoring and validation               │
│  - Go/No-Go decision before next batch             │
└────────────────────────────────────────────────────┘
                    ↓
┌────────────────────────────────────────────────────┐
│  WEEK 8: BATCH 1 - Central Europe                 │
│  - Germany (DE) - Largest volume                   │
│  - Austria (AT) - Medium volume                    │
│  - 48-hour monitoring period                       │
└────────────────────────────────────────────────────┘
                    ↓
┌────────────────────────────────────────────────────┐
│  WEEK 9: BATCH 2 - Western Europe                 │
│  - France (FR) - Medium-high volume                │
│  - Switzerland (CH) - Special regulations          │
│  - 48-hour monitoring period                       │
└────────────────────────────────────────────────────┘
                    ↓
┌────────────────────────────────────────────────────┐
│  WEEK 10: BATCH 3 - Balkans & Regional            │
│  - Croatia (HR) - Low-medium volume                │
│  - Serbia (RS) - Low volume                        │
│  - Regional variants                               │
│  - Final monitoring and sign-off                   │
└────────────────────────────────────────────────────┘
```

### 9.2 Pilot Deployment (Week 7): Bulgaria

**Why Bulgaria?**
- ✅ **Lowest transaction volume** among 8 countries
- ✅ **Simpler regulatory requirements** (no complex narcotics tracking)
- ✅ **Representative system architecture** (same as other countries)
- ✅ **Manageable rollback scope** if issues occur

**Friday Night (2 AM):**
```bash
# 1. Pre-deployment backup
dbexport ksc_bulgaria < discount_backup_bulgaria_20251230.sql

# 2. Stop all CSC applications
systemctl stop csc_core_app_bulgaria

# 3. Deploy code changes
cd /deploy/bulgaria/
./deploy_cpr.sh --country BG --version 2.0.0

# 4. Verify deployment
./verify_deployment.sh --country BG

# 5. Execute Branch 0 data load
./loadconditions.sh -start -vz 0

# 6. Validate data integrity
./validate_branch0_data.sh --country BG

# 7. Restart CSC applications
systemctl start csc_core_app_bulgaria

# 8. Smoke tests
./run_smoke_tests.sh --country BG
```

**Saturday (8 AM - 6 PM):**
- **Real-time monitoring** of error logs, discount calculations, performance
- **Sample 100 orders** and validate discount amounts manually
- **Compare with legacy system** (parallel Branch 1 data still available)
- **Collect performance metrics** (query latency, batch duration)

**Sunday (8 AM - 6 PM):**
- **Continue monitoring** for any delayed issues
- **Reconciliation checks** - compare total discount amounts vs. previous week
- **User acceptance validation** - pharmacies in Bulgaria confirm orders are correct
- **Performance analysis** - analyze 48 hours of metrics

**Monday (Go-Live Decision):**
```
Decision Criteria:
✅ Zero critical errors in error logs
✅ All discount calculations match expected values (100%)
✅ Performance within acceptable range (<= 110% of baseline)
✅ Business users report no issues
✅ Rollback plan NOT executed

IF all criteria MET:
   → Proceed with Batch 1 (Germany + Austria)
ELSE:
   → Pause deployment, analyze issues, fix, re-test
```

### 9.3 Batch Deployments (Week 8-10)

**Batch 1 (Week 8): Germany + Austria**

**Monday Night (2 AM):**
- Deploy to Germany (DE) and Austria (AT)
- Follow same procedure as Bulgaria pilot
- Monitor Tuesday-Wednesday (48 hours)

**Batch 2 (Week 9): France + Switzerland**

**Wednesday Night (2 AM):**
- Deploy to France (FR) and Switzerland (CH)
- Extra validation for Switzerland (strict regulations)
- Monitor Thursday-Friday (48 hours)

**Batch 3 (Week 10): Croatia + Serbia + Regional**

**Friday Night (2 AM):**
- Deploy to Croatia (HR), Serbia (RS), and regional variants
- Monitor Saturday-Sunday (48 hours)
- Final project sign-off Monday

### 9.4 Rollback Procedure

**Decision Criteria for Rollback:**

| Criteria | Threshold | Action |
|----------|-----------|--------|
| **Critical errors in logs** | > 0 errors | Immediate rollback |
| **Discount calculation errors** | > 0.1% orders affected | Immediate rollback |
| **Performance degradation** | > 20% slower | Investigate, possible rollback |
| **Data inconsistency** | Any detected | Immediate rollback |
| **Customer complaints** | > 5 discount-related | Investigate |

**Rollback Time Estimate: 4-6 hours**

**Step 1: APX Scheduler Restore (15 minutes)**
```bash
# Re-enable Branch 1-20 jobs
apx_scheduler --enable LOADCONDITIONS_01
apx_scheduler --enable LOADCONDITIONS_02
# ... (enable all 20 jobs)

# Disable Branch 0 job
apx_scheduler --disable LOADCONDITIONS_00
```

**Step 2: Shell Script Reversion (15 minutes)**
```bash
# Revert loadconditions.sh changes (all 6 countries)
cd /src/environment/
git checkout HEAD~1 -- */ksc/load/proc/loadconditions.sh
```

**Step 3: Binary Redeployment (30 minutes)**
```bash
# Deploy previous version of binaries
cd /deploy/
./deploy_rollback.sh --version 1.9.0
```

**Step 4: Data Reload (2-4 hours)**
```bash
# Run all 20 branch loaders to restore Branch 1-20 data
for branch in {1..20}; do
    nohup ./loadconditions.sh -start -vz $branch &
done

# Wait for all jobs to complete
wait
```

**Step 5: Application Restart & Verification (1 hour)**
```bash
# Restart applications
systemctl restart csc_core_app

# Run verification tests
./run_smoke_tests.sh --all-countries

# Verify discount calculations
./verify_discounts.sh --sample 1000
```

### 9.5 Post-Deployment Validation

**Checklist (Per Country):**

```
┌────────────────────────────────────────────────────┐
│   POST-DEPLOYMENT VALIDATION CHECKLIST             │
├────────────────────────────────────────────────────┤
│ Country: ________ Deployment Date: ___________    │
│                                                    │
│ [ ] Branch 0 data loaded successfully              │
│ [ ] Data integrity validation passed               │
│ [ ] Error logs reviewed (zero critical errors)    │
│ [ ] Discount calculations validated (100 samples) │
│ [ ] Performance metrics collected                  │
│ [ ] User acceptance confirmation                   │
│ [ ] Smoke tests passed (all scenarios)            │
│ [ ] Regression tests passed (1,000 test cases)    │
│ [ ] Parallel data comparison (Branch 0 vs Branch 1)│
│ [ ] Old branch data archived (Branch 1-20)         │
│ [ ] Documentation updated                          │
│ [ ] Stakeholder sign-off obtained                 │
│                                                    │
│ Validator: ________________ Date: __________      │
└────────────────────────────────────────────────────┘
```

**Data Validation Queries:**
```sql
-- Verify Branch 0 has data
SELECT COUNT(*) FROM discount WHERE branchno = 0;
-- Expected: > 0 (at least some records)

-- Verify old branches removed (after cleanup)
SELECT COUNT(*) FROM discount WHERE branchno BETWEEN 1 AND 20;
-- Expected: 0 (after Phase III cleanup)

-- Compare discount totals (Branch 0 vs historical Branch 1)
SELECT 
    SUM(discountvaluepct) as total_discount_branch0
FROM discount WHERE branchno = 0;

SELECT 
    SUM(discountvaluepct) as total_discount_branch1
FROM discount_history WHERE branchno = 1 AND load_date = '2025-12-29';

-- Expected: totals match within 0.01%
```

**Performance Validation:**
```bash
# Overnight batch execution time
grep "loadconditions completed" /var/log/apx/*.log | awk '{print $5}'
# Expected: <6 minutes (vs. 120 minutes before)

# Database storage
dbcc checkalloc('ksc_database', 'discount')
# Expected: 95% reduction in table size

# Query latency (p50, p99)
grep "discount_query_time" /var/log/csc_app/*.log | stats
# Expected: p50 <10ms, p99 <50ms (same as baseline)
```

### 9.6 Final Sign-Off

**Project Completion Criteria:**

```
┌────────────────────────────────────────────────────┐
│      CPR0003319 PROJECT COMPLETION SIGN-OFF        │
├────────────────────────────────────────────────────┤
│ Completion Date: ___________________               │
│                                                    │
│ Deployment Summary:                                │
│   [ ] All 8 countries deployed successfully        │
│   [ ] Bulgaria pilot completed (Week 7)            │
│   [ ] Batch 1 (DE, AT) deployed (Week 8)           │
│   [ ] Batch 2 (FR, CH) deployed (Week 9)           │
│   [ ] Batch 3 (HR, RS, Regional) deployed (Week 10)│
│                                                    │
│ Acceptance Criteria:                               │
│   [ ] 95% data reduction achieved                  │
│   [ ] 15-20x batch performance improvement         │
│   [ ] Zero data loss                               │
│   [ ] Zero financial discrepancies                 │
│   [ ] All regression tests passed (100%)           │
│   [ ] All UAT tests passed (96/96)                 │
│   [ ] Business sign-off from all countries         │
│                                                    │
│ Post-Deployment Metrics:                           │
│   Batch Duration: _____ min (target: <6 min)      │
│   Storage Reduction: _____% (target: 95%)          │
│   Query Latency p50: _____ ms (target: <10ms)     │
│   User Satisfaction: _____ /5.0 (target: >=4.0)   │
│                                                    │
│ Approvals:                                         │
│   Project Manager: ______________ Date: ______    │
│   Technical Lead: _______________ Date: ______    │
│   Business Owner: _______________ Date: ______    │
│   Quality Assurance: ____________ Date: ______    │
│                                                    │
│ [ ] PROJECT APPROVED FOR COMPLETION                │
└────────────────────────────────────────────────────┘
```

---

## 10. Appendices

### Appendix A: Glossary

| Term | Definition |
|------|------------|
| **APX** | Job scheduling system for batch processing |
| **Branch 0** | Special designation for country-level shared data |
| **CDM** | Central Data Maintenance - master data management system |
| **CPR** | Change Production Release |
| **CSC_CORE** | Runtime applications that read discount data |
| **CSC_LOAD** | Batch loaders that write discount data to database |
| **KSC** | Kunden Service Center (Customer Service Center) backend |
| **LDDISCOUNT** | Local Discount table in KSC database (has BRANCHNO) |
| **NTTD** | Narcotics Tracking and Tracing Database |
| **PHARMOS** | Pharmaceutical distribution system |
| **PXDB** | Database access layer with SQL cursors |
| **PXVERBUND** | Core discount calculation engine |
| **Thrift** | Apache Thrift - RPC framework for service interfaces |
| **ZDP** | Zentrales Datenpool (Central Data Pool) - source system |
| **ZDISCOUNT** | Source discount table in ZDP (no BRANCHNO) |

### Appendix B: Four Developer Analysis Comparison

Based on analysis of OUTPUT, OUTPUT02, OUTPUT03, OUTPUT04 folders:

| Developer | Score | Strengths | Weaknesses | Best Use Case |
|-----------|-------|-----------|------------|---------------|
| **Developer #1 (OUTPUT)** | 83/100 | ✅ Found blocking code (loadconditions.sh line 220)<br>✅ Detailed C++ file analysis<br>✅ Specific function names | ❌ No future architecture<br>❌ No country rules | **Phase I & II implementation** |
| **Developer #2 (OUTPUT02)** | 88/100 | ✅ New table designs (3 tables)<br>✅ Service architecture<br>✅ Country-specific rules (8 countries)<br>✅ API contracts | ❌ Missing critical code details<br>❌ Over-engineered for CPR scope | **Phase III future enhancements** |
| **Developer #3 (OUTPUT03)** | 78/100 | ✅ Strategic synthesis<br>✅ Comparison matrix<br>✅ Meta-analysis | ❌ No original technical analysis<br>❌ Shorter length | **Project management perspective** |
| **Developer #4 (OUTPUT04)** | 92/100 ⭐ | ✅ Most comprehensive (1,491 lines)<br>✅ Complete DB schema (45 fields)<br>✅ 24+ test cases<br>✅ 5-week deployment plan<br>✅ Risk matrix | ❌ Some redundancy<br>❌ Missing country rules | **PRIMARY IMPLEMENTATION GUIDE** |

**Recommended Hybrid Approach:**
- **Use OUTPUT04 as primary guide** (most comprehensive)
- **Supplement with OUTPUT** for critical code fixes (loadconditions.sh)
- **Refer to OUTPUT02** for Phase III improvements (new tables, services)

### Appendix C: Country-Specific Discount Rules (from OUTPUT02)

| Country | Max Discount | Min Margin | Stackable | Approval Required | Special Notes |
|---------|--------------|------------|-----------|-------------------|---------------|
| **CH** (Switzerland) | 15% | 18% | No | Always | Strictest regulations |
| **AT** (Austria) | 20% | 15% | No | Yes | Medium regulations |
| **DE** (Germany) | 25% | 12% | Yes | No | Most flexible |
| **BG** (Bulgaria) | 18% | 13% | No | No | Pilot country (low volume) |
| **FR** (France) | 22% | 11% | No | No | Special VAT rules |
| **HR** (Croatia) | 20% | 14% | No | No | EU member rules |
| **RS** (Serbia) | 22% | 12% | No | No | Non-EU special handling |

**Note:** These rules should be implemented in Phase III using new tables (country_discount_rules).

### Appendix D: SQL Metadata Inspection Results

**From related_common/informix_sql_inspection:**

**discount table schema:**
```sql
-- Table: discount
-- Columns: 45+ fields
-- Primary Key: (BRANCHNO, ARTICLENO, DISCOUNTGRPNO, PHARMACYGROUPID, CUSTOMERNO)
-- Indexes: 5 composite indexes (all start with BRANCHNO)
-- Storage: ~2M-10M rows × 20 branches = 40M-200M total rows
-- Current Size: ~10-20 GB per country
-- After CPR: ~1 GB per country (95% reduction)
```

**Index Statistics:**
```sql
-- Index: i_discount_1
-- Columns: (BRANCHNO, ARTICLENO, DISCOUNTTYPE, PHARMACYGROUPID)
-- Selectivity: 5% (1/20 branches)
-- Usage: Very High (90% of queries)
-- After CPR: Selectivity drops to 0% (BRANCHNO=0 always matches 100%)
```

### Appendix E: APX Job Configuration Details

**Current APX Configuration (20 Jobs):**
```ini
[Job LOADCONDITIONS_01]
Schedule = 02:00 daily
Command = /ksc/load/proc/loadconditions.sh -start -vz 1
Dependencies = ZDP_TRANSFER_COMPLETE
Timeout = 30 minutes
ErrorAction = NOTIFY_ADMIN

[Job LOADCONDITIONS_02]
Schedule = 02:00 daily
Command = /ksc/load/proc/loadconditions.sh -start -vz 2
Dependencies = ZDP_TRANSFER_COMPLETE
Timeout = 30 minutes
ErrorAction = NOTIFY_ADMIN

# ... (repeat for jobs 03-20)
```

**Proposed APX Configuration (1 Job):**
```ini
[Job LOADCONDITIONS_00]
Schedule = 02:00 daily
Command = /ksc/load/proc/loadconditions.sh -start -vz 0
Dependencies = ZDP_TRANSFER_COMPLETE
Timeout = 10 minutes  # Reduced from 30 minutes
ErrorAction = NOTIFY_ADMIN
```

### Appendix F: Contact Information

| Role | Name | Email | Responsibility |
|------|------|-------|----------------|
| **Project Manager** | TBD | TBD | Overall project coordination |
| **Technical Lead** | TBD | TBD | Architecture and implementation |
| **Database Administrator** | TBD | TBD | Schema changes, performance |
| **QA Lead** | TBD | TBD | Testing strategy and execution |
| **Business Analyst** | TBD | TBD | Requirements and UAT |
| **Incident Contact** | Frank Naumann | TBD | Related to 01.07.2025 incident |
| **Compliance Officer** | TBD | TBD | GxP validation |

### Appendix G: Reference Documents

1. **CPR0003319 Original Specification** - INPUT/CPR_received/
2. **Developer Analysis #1 (OUTPUT)** - OUTPUT/CPR0003319_Analysis_Complete.md
3. **Developer Analysis #2 (OUTPUT02)** - OUTPUT02/README.md
4. **Developer Analysis #3 (OUTPUT03)** - OUTPUT03/CPR0003319_Comprehensive_Analysis_V3.md
5. **Developer Analysis #4 (OUTPUT04)** - OUTPUT04/CPR_Technical_Analysis.md
6. **Comprehensive Comparison** - REVIEW/COMPREHENSIVE_CPR_ANALYSIS_COMPARISON.md
7. **Executive Summary** - REVIEW/EXECUTIVE_SUMMARY.md
8. **Quick Reference Card** - REVIEW/QUICK_REFERENCE_CARD.md

### Appendix H: Version History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | 2025-12-30 | AI Analysis | Initial draft |
| 0.5 | 2025-12-30 | AI Analysis | Added layer-by-layer analysis |
| 1.0 | 2025-12-30 | AI Analysis | **Complete analysis document** |

---

## Document Summary

This comprehensive analysis document provides:

1. ✅ **Complete understanding of CPR0003319** - what it is, why it's needed, how it works
2. ✅ **Full inventory of impacted files** - 153 files across 6 packages
3. ✅ **Layer-by-layer orchestration** - clear explanation of changes in each architectural layer
4. ✅ **Detailed implementation plan** - phased approach with week-by-week tasks
5. ✅ **Risk assessment and mitigation** - 10 risks with detailed mitigation strategies
6. ✅ **Comprehensive testing strategy** - unit, integration, regression, performance, UAT
7. ✅ **Phased deployment plan** - pilot + 3 batches with rollback procedures
8. ✅ **Validation of all 4 developer approaches** - hybrid recommendation using best of each

**Status:** ✅ **READY FOR IMPLEMENTATION**

**Next Steps:**
1. Review and approve this analysis document
2. Assemble implementation team
3. Set up test environment
4. Begin Phase I (Week 1-2): Enable Branch 0 loading
5. Continue with Phase II (Week 3-6): Update applications
6. Pilot deployment in Bulgaria (Week 7)
7. Full rollout (Week 8-10)

---

**Document End**

**For questions or clarifications, please refer to the specific sections above or contact the project team.**
