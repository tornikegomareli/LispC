(+ 1 2)                  ; Simple: add 1 and 2
(+ 1 2 3 4 5)           ; Variadic: add five numbers
(* (+ 2 3) 4)           ; Nested: (2+3) * 4
(+ (* 2 3) (- 8 3))     ; Multiple nesting: (2*3) + (8-3)
```

### **Why Fully Parenthesized?**

**Traditional infix:** `2 + 3 * 4`
- Is it `(2 + 3) * 4 = 20`?
- Or `2 + (3 * 4) = 14`?
- Need precedence rules (PEMDAS)
- Parser complexity increases

**S-Expression:** `(+ 2 (* 3 4))`
- **Zero ambiguity** - structure is explicit
- Parser becomes trivial
- Code structure = AST structure
- What you write is what gets executed

### **Visual Tree Representation**

For expression: `(* 2 (+ 3 4))`
```
Text form:                Tree form:
                            
(* 2 (+ 3 4))                 *
                             / \
                            2   +
                               / \
                              3   4

Evaluation flow:
1. Evaluate (+ 3 4) → 7
2. Evaluate (* 2 7) → 14
