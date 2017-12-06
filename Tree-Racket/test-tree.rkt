ng racket

(provide tree-test)

(require "tree.rkt")

(define (tree-test)
  (let* ( [lt1a (leaf "leaf 1a")]
  	  [lt1b (leaf "leaf 1b")]
	  [mid1 (tree "mid-node 1" (list lt1a lt1b))]
	  [lt2a (leaf "leaf 2a")]
  	  [lt2b (leaf "leaf 2b")]
  	  [lt2c (leaf "leaf 2c")]
	  [mid2 (tree "mid-node 2" (list lt2a lt2b lt2c))]
	  [top  (tree "top node"   (list mid1 mid2))]
          [top-2 (tree "top node" (list mid1 mid2))]
          [top-3 (map-function add-! top)]
          )
 	(and
	 (tree? lt1a)
	 (tree? mid2)
	 (not (tree? "This is not a tree. Or a pipe. Or an exit. It is a string."))
         (leaf? lt1a)
         (not (leaf? mid1))
         (equal? (tree-root-value lt1a) "leaf 1a")
	 (equal? (tree-root-value top) "top node")
	 (equal? (tree-root-value (tree-child-i top 0)) "mid-node 1")
         (tree-equal? top top-2)
          ;(map-function top)
         ;(foldl-function stringappend top)
         
    )))

(define (tree-demo)
   (let* ( [lt1a (leaf "leaf 1a")]
  	  [lt1b (leaf "leaf 1b")]
	  [mid1 (tree "mid-node 1" (list lt1a lt1b))]
          [mid3 (tree "mid-node 3" (list lt1b mid1))]
	  [lt2a (leaf "leaf 2a")]
  	  [lt2b (leaf "leaf 2b")]
  	  [lt2c (leaf "leaf 2c")]
	  [mid2 (tree "mid-node 2" (list lt2a lt2b lt2c))]
	  [top  (tree "top node"   (list mid1 mid2))]
          [top-2 (tree "top node" (list mid1 mid2))]
          [top3 (tree "top node 3" (list mid3 mid2))]
          [ch1 (leaf "Ch1: Intro")]
          [ch2 (leaf "Ch2: Analysis")]
          [ch3 (leaf "Ch3: Elementary")]
          [ch4 (leaf "Ch4: ADT's")]
          [ch5 (leaf "Ch5: Trees")]
          [ch6 (leaf "Ch6: Elementary")]
          [ch7 (leaf "Ch7")]
          [part1 (tree "Chapter 1: Fundamentals" (list ch1 ch2))]
          [part2 (tree "Chapter 2: Data Structures" (list ch3 ch4 ch5))]
          [part3 (tree "Part 3: Sorting" (list ch6 ch7))]
          [s_5_19 (tree "Algorithms" (list part1 part2 part3))]
          [s_5_19_1 (map-function add-! s_5_19)]
          )
          
     (and
      (equal? 3 (height top3))
      (equal? 10 (size top3))
      (equal? "top node 3 mid-node 3  leaf 1bmid-node 1  leaf 1a leaf 1b  mid-node 2  leaf 2a leaf 2b leaf 2c  "
              (foldl-function stringappend top3))
      (equal? 2 (height s_5_19))
      (equal? "Algorithms! Part 3: Sorting!  Ch7! Ch6: Elementary! Chapter 2: Data Structures!  Ch5: Trees! Ch4: ADT's! Ch3: Elementary! Chapter 1: Fundamentals!  Ch2: Analysis! Ch1: Intro!  "
     (foldl-function stringappend s_5_19_1))
      (equal? #t (tree-equal? top-2 top))
     (equal? #f (tree-equal? top3 top))
     (display (af-recursion s_5_19))
     (display "\n")
     (display "\n")
     (display (af-mapfold s_5_19))
      )))
          

