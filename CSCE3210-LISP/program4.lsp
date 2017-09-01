;m kellen mills
;symbolic processing with dr. swigger

(defun profit (x)
	(COND
	  ((NULL x) 0)
	  ((atom (first x)) (- (second x) (third x)))
	  (T (+ (profit (first x)) (profit (rest x))))
	)
)

(defun int-count (x y)
;x is a list of interesting words ;y is a sentence
	(COND
	  ((NULL x) 0)
	  ((atom x) (COND
	;condition sheck for membership in the latter list 
	;and then recursives itself 
	;using a list modified to not have one of the instances of theword which the  member function noticed.
	    ((member x y) (+ 1 (int-count x (remover (my-position y x) y))))
	    (T 0)
	  ))
	  (T (+ (int-count (first x) y) (int-count (rest x) y)))
	)
)

(defun my-position (x y)
;x is a list; y is an atom; atom is searched for in the list.
        (COND
          ((NULL x) 0)
          ((member y x) (+ 1 (my-position (rest x) y)))
          (T (+ 0 (my-position (rest x) y)))
        )
)

(defun remover (x y)
;x is a position ;y is a list
        (COND
          ((NULL y) nil)
          ((= x 1) (remover (- x 1) (rest y)))
          (T (CONS (first y) (remover (- x 1) (rest y))))
        )
)


(defun test ()
;(test) is now a command to test both functions 
	(print (profit '((garden 15000 10000) (kitchen 2000 1000))))
	(print (int-count '(big dog) '(a big dog has a big appetite)))
)
