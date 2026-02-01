# PROJECT CONTEXT: CPP Module 00
**Project:** C++ - Module 00 (42 Curriculum)
**Student:** lahermaciel
**Started:** 2026-01-27
**Last Updated:** 2026-01-31

---

## PROJECT OVERVIEW

### Exercises
- **ex00:** Megaphone (COMPLETED)
- **ex01:** PhoneBook (COMPLETED - Fully implemented and tested)
- **ex02:** IN PROGRESS - Constructor implemented, ~8 functions remaining

### Current Focus
**Exercise 02: Account Class** (IN PROGRESS)
- Started: 2026-01-31
- Status: Constructor complete, static variables defined
- Remaining: _displayTimestamp, getters, displayStatus, displayAccountsInfos, makeDeposit, makeWithdrawal, destructor

---

## REQUIREMENTS & CONSTRAINTS

### Technical Requirements (ex01)
- **Language:** C++98 standard
- **Allowed:** std::string, std::cout, std::cin, iostream, iomanip
- **Forbidden:** External libraries, C-style arrays of char for strings
- **Memory:** No leaks, no crashes
- **Compilation:** Must compile with -Wall -Wextra -Werror

### Functional Requirements
1. **ADD Command:**
   - Prompts for: first name, last name, nickname, phone number, darkest secret
   - Stores up to 8 contacts
   - When 9th contact added, replaces oldest (circular buffer behavior)
   - Empty fields not allowed

2. **SEARCH Command:**
   - Displays all contacts in formatted table (4 columns: index, first name, last name, nickname)
   - Each field truncated to 10 characters max (with trailing dot if truncated)
   - Right-aligned columns
   - Prompts for index to display full contact details
   - Invalid index → appropriate error handling

3. **EXIT Command:**
   - Terminates program (contacts lost)

---

## DESIGN DECISIONS

### Architecture (Validated 2026-01-28)

**Contact Class:**
- **Responsibility:** Store individual contact data
- **Private Data:**
  - std::string first_name
  - std::string last_name
  - std::string nickname
  - std::string phone_number
  - std::string darkest_secret
- **Public Functions:**
  - Setters for each field (with validation)
  - Getters for each field
- **Design Note:** Keep Contact simple - just data container with controlled access

**PhoneBook Class:**
- **Responsibility:** Manage collection of contacts, handle user interactions
- **Private Data:**
  - Contact contacts[8] (fixed array)
  - int contact_count (tracks 0-8, how many valid contacts exist)
  - int next_index (tracks 0-7, circular counter for replacement)
- **Public Functions:**
  - void add() - handles ADD command logic
  - void search() - handles SEARCH command logic
- **Design Note:** PhoneBook owns all business logic (display formatting, validation, user prompting)

**main() function:**
- Creates PhoneBook instance
- Runs command loop (ADD/SEARCH/EXIT)
- EXIT is loop control logic, NOT a PhoneBook method

### Key Design Principles Applied
1. **Encapsulation:** Contact data is private, accessed only through getters/setters
2. **Single Responsibility:** Contact manages data, PhoneBook manages operations
3. **OOP vs Procedural:** Methods belong to classes, not external functions operating on objects
4. **Separation of Concerns:** Data (Contact) vs Behavior (PhoneBook) vs Control Flow (main)

---

## PROGRESS TRACKING

### Session 1 (2026-01-27)
**Status:** Conceptual understanding established
**Achievements:**
- Understood exercise requirements
- Mapped out class structure
- Grasped OOP design principles

**Homework Assigned:**
- Read cplusplus.com classes tutorial
- Watch C++ classes video
- Answer: What are public/private? Declaration vs implementation?

### Session 2 (2026-01-28)
**Status:** Design phase complete, ready for implementation

**Achievements:**
- CRITICAL MINDSET SHIFT: Overcame procrastination pattern through direct confrontation
- Completed homework (read tutorial, watched video, understood access specifiers)
- Asked excellent questions: protected, scope operator (::), inline, encapsulation rationale
- Understood WHY privatization matters (validation, control, gatekeeping)
- Understood interface vs implementation separation (.hpp vs .cpp)
- Designed complete class architecture (Contact + PhoneBook)
- **MAJOR CORRECTION:** Initially proposed procedural design (external functions), recognized mistake, corrected to proper OOP design
- Learned circular buffer replacement strategy (next_index wrapping 0-7)
- Understood need for two tracking variables (contact_count + next_index)

### Session 3 (2026-01-30)
**Status:** ex01 COMPLETED - Full implementation and testing

**Achievements:**
- Implemented Contact.hpp with include guards, 5 private members, 5 setters, 5 const getters
- Implemented Contact.cpp with all 10 method implementations using scope resolution operator
- Implemented PhoneBook.hpp with constructor, private members, public methods
- Implemented PhoneBook.cpp:
  - Constructor initializing total_contacts and next_index to 0
  - get_input() static helper for input validation (empty field re-prompting)
  - add_contact() with all 5 field inputs and circular buffer logic
  - format_field() static helper for 10-char column truncation
  - display_contact() static helper for formatted table output
  - user_info() static helper for full contact display
  - search_contacts() with formatted table, index validation, full contact display
- Implemented MyAwesomePhoneBook.cpp with main command loop (ADD/SEARCH/EXIT)
- Fixed Makefile: added all source files, fixed .c→.cpp pattern rule, added headers/includes
- Wrote trim_string() bonus function for whitespace handling
- **FULLY TESTED**: ADD, SEARCH, EXIT, empty fields, invalid commands, invalid indices, circular buffer replacement, truncation

**Concepts Learned This Session:**
- Header file structure (include guards, declarations vs implementations)
- Constructors (automatic initialization, no return type)
- Scope resolution operator (ClassName::method)
- std::getline vs std::cin (whitespace handling, buffer issues)
- std::setw and iomanip for formatted output
- std::string methods (length, substr, empty, find_first_not_of, find_last_not_of, c_str)
- atoi for string-to-int conversion (C++98)
- const member functions (promise not to modify object)
- Static standalone helper functions
- Makefile pattern rules for C++ compilation
- Input validation strategies

**Performance Note:** Exceeded minimum threshold significantly. Minimum was headers + one method. Student completed entire exercise in one session. Previously predicted 6-8 hours across 3 sessions.

**Behavioral Note:** No procrastination observed. Maintained focus throughout. Asked good conceptual questions before coding (why const? why separate files? how do objects work in memory?). Self-corrected when guided. Good instinct for code organization (proposed helper functions independently).

---

## KNOWN ISSUES

### Current Blockers
1. **ex02 incomplete:** Constructor done, 8 functions remaining (_displayTimestamp, 4 getters, displayStatus, displayAccountsInfos, makeDeposit, makeWithdrawal, destructor)
2. **Knowledge gap:** C time functions (time, localtime, struct tm) - assigned as homework

### Risks to Monitor
1. **TIME PRESSURE - CRITICAL:** Student has deadline March 1st for multiple modules (CPP00-04 minimum). Currently behind pace.
2. **Stopping pattern:** Session 4 stopped at moderate progress despite stating commitment to goals. Pattern to monitor - may indicate task avoidance when faced with unfamiliar topics (time functions research).

---

## TESTING STATUS

### ex01 - FULLY TESTED
- ADD command: normal inputs, empty field re-prompting ✓
- SEARCH command: formatted table, truncation, valid/invalid index ✓
- EXIT command: clean termination ✓
- Circular buffer: 9th+ contacts replace oldest correctly ✓
- Invalid commands: rejected with error message ✓
- Compiles with -Wall -Wextra -Werror ✓

---

## SESSION LOGS

### 2026-01-27: Initial session
- Requirement analysis
- Conceptual understanding of OOP
- Homework assigned

### 2026-01-28: Design phase
**Critical Moment:** Student admitted procrastination, wanted to defer to tomorrow. Confronted pattern directly. Student chose to engage immediately instead of postponing - significant self-discipline demonstration.

**Learning Outcomes:**
- Deep understanding of public/private (not just what, but WHY)
- Encapsulation as validation/control mechanism
- Interface vs implementation separation
- Scope operator (::) purpose
- Inline concept (understood but not needed for project)
- Protected access specifier (deferred to later modules)

**Behavioral Pattern Observed:** Student demonstrates exceptional honesty and self-awareness. When confronted with avoidance behavior, responds positively to direct challenge and course-corrects. Requested accountability mechanism (minimum progress threshold) - shows strategic thinking about own weaknesses.

**Quality of Questions:** Excellent. Not surface-level syntax questions, but "why do we do it this way?" questions. Shows critical thinking.

**Design Evolution:** Initially proposed procedural approach (external functions), immediately recognized this defeats OOP purpose when explained. Shows strong learning agility.

**Accountability Request:** Student requested "secret minimum progress threshold" to prevent premature session ending. Shows maturity and awareness of own tendencies.

**Session End Status:** Ended appropriately due to late hour, with clear homework (3 verification questions). Student showed enthusiasm about potentially exceeding minimum threshold.

**Process Improvement:** Student requested automatic context file updates at session end to eliminate mental overhead of remembering. Implemented as standard procedure - files will auto-update on session endings and major milestones.

### Session 4 (2026-01-31)
**Status:** ex02 IN PROGRESS - Foundational work, moderate code progress

**Achievements:**
- Repository restructuring: Renamed CPP_Module_XX to CPPXX for brevity
- Git practices: Updated .gitignore (executables, *.tmp pattern), clean commit workflow
- Understood static vs instance members (class-level vs object-level variables)
- Understood private constructors as design pattern (enforcing invariants)
- Implemented Account.cpp static variable definitions (4 static members initialized)
- Implemented Account constructor with proper member initialization
- **CRITICAL BUG FIXED:** Caught and corrected shadowing bug (declaring local vars instead of assigning to members)
- Understood timestamp format requirements from log file

**Concepts Learned This Session:**
- Static class members (shared across all instances, one copy for entire class)
- Static member functions (can be called without object instance)
- Static variable definition requirement (declare in .hpp, define in .cpp at file scope)
- Private constructors preventing default instantiation
- Log file as specification (reverse-engineering approach)
- Variable shadowing bug (int _var = x creates NEW local, not assigns to member)

**Progress Assessment:** BELOW minimum threshold
- Minimum: "ex02 completed OR significant progress"
- Actual: Moderate progress (1 of ~9 functions implemented)
- Positive: Strong conceptual understanding, clean development practices
- Concern: Time pressure with March 1st deadline looming

**Behavioral Note:** Student chose to research time functions independently rather than accept direct solution, even when tired late at night. Shows commitment to genuine learning over shortcuts. However, chose to stop before completing research/implementation - pattern to monitor.

**Session End Status:** Stopped late at night. Committed to "compensate tomorrow" by finishing ex02 + starting CPP01.

---

## NOTES FOR NEXT SESSION

### Homework Before Next Session:
1. Research C time functions on cplusplus.com (20 min):
   - time() - getting current time
   - localtime() - converting to date/time components
   - struct tm - members tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec
   - Note the gotchas: tm_year (years since 1900), tm_mon (0-11 for Jan-Dec)
2. Review log file format to understand function outputs

### Start Session With:
1. Implement _displayTimestamp() using researched time functions
2. Continue with remaining ex02 functions in order:
   - Static getters (getNbAccounts, getTotalAmount, etc.) - simple
   - displayStatus() - shows individual account info
   - displayAccountsInfos() - shows summary using getters
   - makeDeposit() - modifies account, updates static totals
   - makeWithdrawal() - modifies with validation (can fail if insufficient funds)
   - Destructor - cleanup and logging

### Success Criteria for Next Session (Minimum Progress Threshold):
**CRITICAL - Student is behind schedule**
- **MANDATORY:** Complete ex02 fully (all functions implemented and tested against log file)
- **STRETCH GOAL:** Begin CPP Module 01 to compensate for Session 4 shortfall
- March 1st deadline requires finishing CPP00-04 minimum - pace needs to increase

### Teaching Points to Emphasize:
- Student has proven they can implement full classes from scratch
- Focus on reading and understanding existing code (ex02 provides header)
- Continue building on OOP fundamentals toward inheritance, polymorphism in later modules

---

## STANDARDS CHECKLIST (To Verify During Implementation)

### C++ Standards (ex01)
- [x] Compiles with -Wall -Wextra -Werror (no warnings)
- [x] C++98 compliant (no C++11 features)
- [ ] No memory leaks (valgrind clean) - not yet tested
- [x] No segfaults
- [x] Proper use of std::string (no C char arrays)

### Code Quality (ex01)
- [x] Clear variable/function names
- [x] Proper encapsulation (private data, public interface)
- [x] Input validation on all user inputs
- [x] Error handling for invalid indices
- [x] Clean formatting and readability

### 42 Specific (ex01)
- [ ] Orthodox Canonical Form (if required by subject - verify)
- [x] File structure: .hpp headers, .cpp implementations, Makefile
- [x] Makefile rules: all, clean, fclean, re
- [x] No forbidden functions used

---

## REFLECTION

**Project Difficulty for Student:** Moderate. The conceptual shift from C to OOP was the main challenge, successfully overcome.

**Student Performance:** Exceeded all expectations. Completed entire ex01 in one session (Session 3) when predicted to need 3 sessions. Strong C foundation translates well to C++. Asks conceptual "why" questions, not just "how" questions. Good instinct for code organization (independently proposed helper functions, trim utility).

**Confidence Level:** 9/10 for remaining modules. Student has demonstrated ability to learn new concepts and apply them immediately.

**Remaining Work for CPP Module 00:**
- ex02: Account class (recreate class from provided header/test files)

**Modules Remaining (42 CPP curriculum):**
- CPP Module 00: ex02 remaining
- CPP Module 01: Memory allocation, references, pointers to members, switch
- CPP Module 02: Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form
- CPP Module 03: Inheritance
- CPP Module 04: Subtype polymorphism, abstract classes, interfaces
