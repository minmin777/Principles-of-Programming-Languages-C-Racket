;
;  This file is for implementing the postfix calculator in Racket
;
#lang racket
(provide (all-defined-out))
(require "stack.rkt")


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; These "calc-" functions implement various calculator operations,
;   such as popping two numbers, adding them, and pushing the results
;
; Each returns the resulting stack (even if it isn't modified, as for .s)
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Takes in a stack; returns a new stack with the two old elements that were
;on top added and pushed into the new stack
(define (calc-add a-stack)
    (if (< (stack-size a-stack) 2)
        (error "not enough elements in stack to add")
        (let ((top-a (stack-top a-stack)) ;top-a is the top element of the stack
              (pop-b (stack-pop a-stack))) ;pop-b is a new stack with the top of a-stack is taken out
          (stack-push (stack-pop pop-b) (+ top-a (stack-top pop-b))))))

;Takes in a stack; returns an updated stack with the two old tops subtracted together and pushed into the new stack
(define (calc-subtract a-stack)
  (let ((top-a (stack-top a-stack));top-a is the top element of the stack
        (pop-b (stack-pop a-stack)));pop-b is a new stack with the top of a-stack is taken out
    (if (< (stack-size a-stack) 2)
        (error "not enough elements in stack to subtract")
        (stack-push (stack-pop pop-b) (- (stack-top pop-b) top-a)))))
    
;Takes in a stack; returns an updated stack with the two old tops multiplied toegtehr and popped into a new stack
(define (calc-multiply a-stack)
  (let ((a (stack-top a-stack));top-a is the top element of the stack
        (b (stack-pop a-stack)));pop-b is a new stack with the top of a-stack is taken out
    (if (< (stack-size a-stack) 2)
        (error "not enough elements in stack to multiply")
        (stack-push (stack-pop b) (* a (stack-top b))))))

;Takes in a stack; returns a new stack where the top is gone and displays the old top
(define (calc-. a-stack)
  (cond
    [(stack-empty? a-stack) (error "not enough elements in stack to pop")]
    [else (display " ") (display (stack-top a-stack)) (display " ") (stack-pop a-stack)]))


;Takes in a stack; displays the size of the stack and then displays the stack where the top is displayed at the end
(define (calc-.s a-stack) ;doesn't return a stack 
  (display "<")
  (display (stack-size a-stack))
  (display ">")
  (reverse-stack a-stack)
  (the-stack a-stack))

; Takes in a stack and returns a stack with the top popped but doesn't display it
(define (calc-drop a-stack) ;a-stack is a stack
  (if (= (stack-size a-stack) 0)
      (error "not enough elements in stack to drop")
      (stack-pop a-stack))) ; returns a-stack with top popped off

(define (calc-nip a-stack) ;a-stack is a stack you want to put in and returns a stack with w1w2-w2 so no w1 in the stack
  (let ((top-a (stack-top a-stack)) ;top-a is the top of a-stack
        (pop-a (stack-pop a-stack))) ; want to make a new stack with a-stack top popped off so we can add to it
  (if (< (stack-size a-stack) 2)
      (error "not enough elements in stack to nip")
      (stack-push (stack-pop pop-a) top-a)))) ;returns a new stack with just top-a
;stack-pop pop-a is a new stack with the second top popped off we don't want this alue

(define (calc-dup a-stack) ; takes in a stack and returns a new stack with the top pushed again so the top of a-stack is duplicated w-ww with w being the stack
  (let ((top-stack (stack-top a-stack))) ; top-stack is an int with the top of a-stack
    (stack-push a-stack top-stack))) ;returns a new stack

(define (calc-over a-stack) ; takes in a stack and returns a new stack with w1w2-w1w2w1 where w1 is bottom of the top and w2 is the top
  ;so we want to push the bottom of a-stack and return this new stack
  (let ((top2 (stack-top (stack-pop a-stack))) ; top2 is the top of a-stack so an int
        (push1 (stack-push (stack-pop a-stack) (stack-top a-stack))))
    (if (< (stack-size a-stack) 2)
        (error "not enough elements in stack to dup")
        (stack-push push1 top2)))) ; a stack is returned

(define (calc-tuck a-stack) ; takes in a stack, a-stack, and returns a stack with w1w2-w2w1w2 with w2 being the top of the stack and w1 is under the top
  (if (< (stack-size a-stack) 2)
      (error "not enough elements in stack to tuck")
      (let* ((top4 (stack-top a-stack)) ;an int with the top of a-stack
             (poptuck1 (stack-pop a-stack)) ; a stack with the top being oppoed off of stack a-stack
             (toptuck2 (stack-top poptuck1))
             (poptuck2 (stack-pop poptuck1))
             (pushtuck1 (stack-push poptuck2 toptuck2))
             (pushtuck2 (stack-push pushtuck1 top4)))
        (stack-push pushtuck2 toptuck2))))

(define (calc-swap a-stack) ; takes in a stack, a-stack
  ;returns a new stack where in the stack the top two elements are switched w1w2-w2w1
  (if (< (stack-size a-stack) 2)
      (error "not enough elements in stack to swap")
      (let* ((top-a (stack-top a-stack))
            (pop-a (stack-pop a-stack))
            (top-b (stack-top pop-a))
            (pop-b (stack-pop pop-a))
            (push-a (stack-push pop-b top-a)))
        (stack-push push-a top-b))))

(define (equal a-stack) ; takes in a stack a-stack
  ;returns a new stack where it pops off the top two elements and sees if they are the same and if they are the same pushes the value -1 and if they aren't pushes into the stack a 0
  (if (< (stack-size a-stack) 2)
      (error "not enough elements in stack to equal")
      (let* ((top-a (stack-top a-stack))
            (pop-a (stack-pop a-stack))
            (top-b (stack-top pop-a))
            (pop-b (stack-pop pop-a)))
        (if (equal? top-a top-b)
            (stack-push pop-b -1)
            (stack-push pop-b 0)))))

(define (greaterthan a-stack) ; takes in a stack, a-stack
  (if (< (stack-size a-stack) 2) ;returns a new stack where it pops off the top two elements and sees if w1w2, the stack, w1 > w2 and if true pushes the value -1 and if false pushes into the stack a 0
      (error "not enough elements in stack for greater than")
      (let* ((top (stack-top a-stack))
            (pop-a (stack-pop a-stack))
            (bottom (stack-top pop-a))
            (pop-b (stack-pop pop-a)))
        (if (> bottom top)
            (stack-push pop-b -1)
            (stack-push pop-b 0)))))

(define (lessthan a-stack) ; takes in a stack, a-stack
  (if (< (stack-size a-stack) 2)
      (error "not enoug elements in stack for less than")
      (let* ((top (stack-top a-stack))
            (pop-a (stack-pop a-stack))
            (bottom (stack-top pop-a))
            (pop-b (stack-pop pop-a)))
        (if (< bottom top)
            (stack-push pop-b -1)
            (stack-push pop-b 0)))));returns a new stack where it pops off the top two elements and sees if w1w2, the stack, w1 < w2 and if true pushes the value -1 and if false pushes into the stack a 0

      


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; below this point is the work to get input and apply functions based on the input
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; first, a conveniente calculator-trace function that prints output but can
;  all be turned off with this calculator-trace-on variable

(define calculator-trace-on #f) ; set to #f when not watching it tell you what its doing

(define (calculator-trace string)
  (if calculator-trace-on
      (begin (display string) #t)
      #t))  ; don't actually care about the returned value, but Racket wants an 'else'


; Transform is a function which takes a stack and a character and
; changes the stack based on it. This is where you will implement your
; various stack transformations.
;
; Input: `a-stack` is a stack, `input` is either a number or a symbol.
; 
; If the user inputs something other than a number or a symbol, fail
; and continue.
; 
; Output: a new transformed stack.
(define ht (hash "+" calc-add "-" calc-subtract "*" calc-multiply "." calc-. ".s" calc-.s "drop" calc-drop "nip" calc-nip "dup" calc-dup "over" calc-over "tuck" calc-tuck "swap" calc-swap "=" equal ">" greaterthan "<" lessthan))
;https://docs.racket-lang.org/guide/hash-tables.html -- where i got learned about hash in racket
(define (transform a-stack input)
  (if (string->number input)  ; gives false if it's not an number, anything else counts as true
      (begin
        (stack-push a-stack (string->number input)))
      (begin ;how you want to transform the stack like if + then do )stack-add
        (cond
          [(let* ((hash-output(hash-ref ht input))) (hash-output a-stack))]
          [else (calculator-trace (format "not sure what to do about ~a, so just popping the stack\n" input))])
      )))

; Process each command in strings and transform the stack Make sure
; you process strings in left-to-right order. Return the resulting
; stack after applying the proper transformation for each command.
; 
; Input:
;  - starting-stack, which is a stack
;  - list-of-strings, which is a list of strings @FIX THIS: (currently must be only one)
; 
; Output: a stack, which has been transformed based on the commands in
; strings.
; 
; Hint: consider using foldl for this. It can be done within ~80
; characters this way. It will be necessary to use "transform" within
; the definition of this function.
;if input is 7 + 3 2 then recursion to go through each
(define (process-commands starting-stack list-of-strings)
  (foldl (lambda (list-strings a-stack) (transform a-stack list-strings)) starting-stack list-of-strings))



; Here we implement a Read-Eval-Print-Loop using tail-recursion in
; Racket.
; 
; input: a stack. This function will perform a tail-call to itself
; with an updated stack until the program is terminated (e.g., via
; ctrl-C).
; 
(define (repl current-stack)
  (begin
    ; Do something here to read the next line, split up each command,
    ; and then transform the stack based on that. Then, call `repl`
    ; with the updated stack.
    (display " C> ")  ; provide a Calculator prompt, a bit different from Racket's
    ; Note: we simply include this to demonstrate how to read a
    ; line. This implementation is incomplete, and will not function
    ; properly (updating the stack) until you implement it correctly.
    (let* ((input (read-line))
           (input-tokens (string-split input))
           ; (ignored1  (calculator-trace (format "got tokens ~a\n" input-tokens)))
           (next-stack (process-commands current-stack input-tokens)))
      (repl next-stack))))
    ; an experienced Racket programmer would just write
    ;  (repl (process-commands current-stack (string-split (read-line))))))

; Type in commands / numbers
; E.g.,
; > 12 13 + . 
; > .s
; (repl (stack))

; If you want to enable the repl, call (note this won't work until you implement stack):
;    (repl (stack))



(define (test-calc)
  (let* ((stack-one (process-commands (stack) '("7" "9" "over" ".s"))))
    ;(process-commands (stack) '("7" "7" "+" "dup" "3" "2" ".s"))
    
    (display "\n")
    (display "The next example takes the stack that was produced from the example above: \n")
    (process-commands stack-one '("8" "10" "9" "." "-" "4" "*" ".s"))
    (display "This next example takes the same sequence of instructions but uses an empty stack: \n")
    (process-commands (stack) '("1" "2" "3" "4" "5" "6" "=" ">" "<" ".s"))
    (process-commands (stack) '("8" "10" "9" "7" "1" "drop" "." "-" "4" "*" ".s"))
    ;(process-commands (stack) '("7" "+" "3" "2" ".s"))
    ))


(display (test-calc))


