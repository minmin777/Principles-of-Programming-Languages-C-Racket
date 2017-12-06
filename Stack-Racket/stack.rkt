;; This is the stack.rkt file for the Stack-Racket project. 
;; 
;; This file implements a stack in Racket and provides a constructor
;; mk-stack and a set of useful functions with names starting "stack-"
;;
#lang racket
(provide
   stack
   stack-empty?
   stack-size
   stack-top
   stack-pop
   stack-push
   stack-equal?
   reverse-stack
   the-stack)

(struct stack-rep (list-of-ints size))

;create an empty stack
(define (stack)
 (stack-rep '() 0))

; check if the stack is empty
;takes a stack
(define (stack-empty? a-stack)
  (if (null? (stack-rep-list-of-ints a-stack))
      #t
      #f))
  

; Takes a stack, returns the number of elements in the stack, in constant time (unlike the list length operation)
(define (stack-size a-stack)
  (stack-rep-size a-stack))

;return the top element of the stack a-stack
(define (stack-top a-stack)
  (car (stack-rep-list-of-ints a-stack)))
  

; returns a new stack formed by popping
; the top element from a-stack
(define (stack-pop a-stack)
  (stack-rep (cdr (stack-rep-list-of-ints a-stack)) (- (stack-rep-size a-stack) 1)))
  ;(stack-rep (cdr (stack-rep-list-of-ints a-stack)) (- (stack-rep-size a-stack) 1)))

; push an element onto the stack and return
; the new stack
(define (stack-push a-stack element)
 (stack-rep (cons element (stack-rep-list-of-ints a-stack)) (+ (stack-rep-size a-stack) 1)))

; Takes two stacks, returns #t if they are equal, #f otherwise
(define (stack-equal? a-stack another-stack)
  (if (equal? (stack-rep-list-of-ints a-stack) (stack-rep-list-of-ints another-stack))
      #t
      #f))


;Takes two stacks, prints out each element in the list but the list is reversed so the top element is
;printed last
(define (reverse-stack aStack )
  (let* ((reglists (foldl cons '() (stack-rep-list-of-ints aStack))))
    (for-each (lambda (i) (if (equal? "#<void>" i) (display " ") (display i)) (display " ")) reglists)))
;foldl function https://docs.racket-lang.org/reference/pairs.html#%28def._%28%28lib._racket%2Fprivate%2Flist..rkt%29._foldl%29%29
;for-each https://docs.racket-lang.org/reference/pairs.html#%28def._%28%28lib._racket%2Fprivate%2Fmap..rkt%29._for-each%29%29

(define (the-stack a-stack)
  (stack-rep (stack-rep-list-of-ints a-stack) (stack-rep-size a-stack)))


 

  

