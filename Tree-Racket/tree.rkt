;; These make drracket treat this file as R5RS scheme:
#lang racket

(provide
  ; *** constructors: provide at least these two:
  leaf              ; takes one parameter a string, returns a leaf containing that value
  tree              ; build a tree from a root value (a string) and a list of subtrees

  ; *** predicates: provide tree? and one or more predicates to detect useful base cases
  tree?             ; predicate to return true if and only if its argument is a valid tree
  leaf?             ; predicate to return true if and only if its argument is a _leaf_
  
  ; *** accessors: provide at least these three
  tree-root-value   ; takes one non-empty tree, returns the root value
  tree-children     ; takes one non-empty tree, returns the list of children
  tree-child-i      ; takes one non-empty tree and an integer i, returns child tree #i

  height
  size
  fold-function
  map-function
  tree-equal?
  ;tree-map
  add-!
  af-recursion
  foldl-function
  stringappend
  af-mapfold
; list other public functions here, but nothing specific to the representation
)

(struct leaf-rep (leaf-string))
(struct tree-rep (tree-string tree-list))

(define (leaf s) ; definition of a leaf takes in a string and puts the string into the struct
  (leaf-rep s))

(define (tree s l) ; definition of a tree where it taks in a string and it's children(list of trees) and puts the string and list in the tree struct
  (tree-rep s l))

(define (tree? t) ; see if the input is a tree - input is a tree t and output is a boolean to see true if a tree or false if not a tree
  (if (tree-rep? t)
      #t
      (if (leaf-rep? t)
          #t
          #f)))
(define (leaf? leaf) ; see if the input is a leaf - input is a tree or leaf and if it's a tree then false and leaf then true - output is a boolean
  (if (tree-rep? leaf)
      #f
      (if (leaf-rep? leaf)
          #t
          #f)))
(define (tree-root-value tree) ; tree is the input of a tree or a leaf and the output is a string which is the value of the tree or leaf
  (if (leaf? tree)
      (leaf-rep-leaf-string tree)
      (if (tree? tree)
          (tree-rep-tree-string tree)
          "")))
(define (tree-children tree) ; the input is a tree and it returns the list of trees which is the tree's children
  (tree-rep-tree-list tree))

(define (tree-child-i-helper tree-list i j) ; helper function for tree-child-i which uses tail recursion; input is tree-list which is a list of trees, i is the desired child tree position in the list, j is always the start so 0
  (if (equal? i j); the output is a tree
      (car tree-list)
      (tree-child-i-helper (cdr tree-list) i (+ j 1))))
(define (tree-child-i tree i) ; tree is a tree and i is the position of the desired i in a list of children of the tree
  (let* ((second-list (tree-rep-tree-list tree)))
    (tree-child-i-helper second-list i 0))) ; output is a tree which is desired child from a tree's children



(define (height a-tree) ;height of a tree where a-tree is a tree to get the height
  (if (leaf? a-tree)
      0 
      (let* ((a-tree-list (tree-rep-tree-list a-tree)))
        (foldl (lambda (l sum) (max sum (+ 1 (height l)))) 0 a-tree-list))))
;(+ 1 (height (car (tree-rep-tree-list a-tree))))
;(+ 1 (height (car (cdr (tree-rep-tree-list a-tree)))))
;learned about max: https://docs.racket-lang.org/reference/generic-numbers.htmls
;returns an int where it is the height of the tree



(define (size a-tree) ; size of a tree where a-tree is the tree that we want to get the size
  (if (leaf? a-tree)
      1
      (let* ((a-tree-list  (tree-rep-tree-list a-tree)))
        (foldl (lambda (l sum) (+ sum (size l))) 1 a-tree-list)))) ;uses foldl to go through the children
;returns an int where it is the size, number of elements, of the tree


(define (tree-equal-helper a-list a-list-two) ;function helper to see if two trees are equal where a-list is the list of children of a tree and a-list-two
  ;is the list of children for the other tree i do this so i can do recursion
  (if (and (empty? a-list) (empty? a-list-two));error if one list is empty and the other isn't
      #t
      (let* ((bool (tree-equal? (car a-list) (car a-list-two))))
        (if (equal? bool #f)
            #f
            (tree-equal-helper (cdr a-list) (cdr a-list-two)))))) ;returns a boolean to see if the lists are the same

; take first of the list and use tree-equal if not go to next
(define (tree-equal? a-tree a-tree-two) ; function to see if two trees are the same
  ;since ordered tree every elements has to be the same and in correct order. a-tree is teh first tree and a-tree-two is the second tree we want to see if equal
  (if (equal? (size a-tree) (size a-tree-two))
      (if (and (leaf? a-tree) (leaf? a-tree-two))
          (if (equal? (tree-root-value a-tree) (tree-root-value a-tree-two))
              #t
              #f)
          (let* ((a-list (tree-rep-tree-list a-tree)) (a-list-two (tree-rep-tree-list a-tree-two)))
            (tree-equal-helper a-list a-list-two)))
      #f))
          
              
          
(define (tree-map-helper a-list) ;helper function to tree-map where a-list if the list of trees or the children of a tree
  (if (equal? (length a-list) 1)
      (car a-list) ;gives the first element of the list which is the tree
      (tree-map-helper (cdr a-list))))
(define (add-! s) ; add an ! at the end of a string which is s
  (string-append s "!"))

(define (map-function f a-tree) ; the map function which takes in a function f and a tree a-tree
  (if (leaf? a-tree)
      (leaf (f (tree-root-value a-tree))) ;if is a-tree is a leaf then the a-tree value is used in the function and creates a leaf
      (let* ((new-tree-list (foldl (lambda (l new-list) (cons (map-function f l) new-list)) (list) (tree-rep-tree-list a-tree))))
        ;new-tree-list is the list of the tree children with a new value as it has been recursed
        (tree (f (tree-root-value a-tree)) new-tree-list)))) ; returns a tree with the new value and the children

(define (fold-function-helper a-tree) 
  ;(string-append (tree-root-value a-tree)
                (foldl (lambda (l a-string) (if (leaf? l) (string-append a-string " " (tree-root-value l))
                                                 (string-append a-string " " (tree-root-value l) " " (fold-function-helper l)))) "" (tree-rep-tree-list a-tree)))
(define (stringappend a-string a-tree-string) ;function for foldl-function to append two strings
  (string-append a-string a-tree-string " "))

(define (fold-function a-tree) ; takes 
 (string-append (tree-root-value a-tree) " " (fold-function-helper a-tree)))

(define (foldl-function f a-tree) ; my fold function for a tree where f is the function we want to use for the foldl where the function takes two strings and returns a string
  ;a-tree is the tree we want to iterate through 
  (if (leaf? a-tree)
      (tree-root-value a-tree)
      (f (tree-root-value a-tree) (foldl (lambda (a-list a-string) (if (leaf? a-list)
                                                                       (string-append a-string " " (tree-root-value a-list))
                                                                       (string-append a-string (foldl-function f a-list))))
                                         " " (tree-children a-tree)))))
(define (af-recursion a-tree) ;my abstraction function with recursion
  ;this representation is so much easier because i can distinguish if the tree input is a leaf or not and create a representation depending on that
  ;i can also add more commas, parantheses and spaces to allow the full representation
  (if (leaf? a-tree) (string-append "(tree " (tree-root-value a-tree) " (list)) ")
      (let* ((first-string (string-append "(tree " (tree-root-value a-tree) "(list ")))
        (string-append first-string (foldl (lambda (list string) (string-append string (af-recursion list))) "" (tree-rep-tree-list a-tree)) "))"))))
;returns a string that representents the abstraction function
(define (af-helper-map string) ;map helper for the abstraction function for map/fold
  (string-append "(tree " string " (list "))
(define (af-mapfold a-tree)
  (let* ((map-variable (map-function af-helper-map a-tree)))
    (string-append (foldl-function stringappend map-variable) ")")))
;with this representation of using map and foldl for tree the foldl function just takes the function, which takes two strings so can't
;see if we can create different representations for a leaf or tree and witht he foldl we are unable to add commas, extra parantheses or spaces
;this is because the map function's function only takes a string so can't use it to distinguish between tree or leaf so i can write different strings to the tree
;depending on if the tree is a leaf or a tree so in the map function all the trees have the same string as it's value for the representation for the abstraction function
;and foldl function just takes those values and string appends them in it's function as the function doesn't allow to distinguish between tree and leaf
