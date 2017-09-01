;M Kellen Mills
;Symbolic Processing with Dr. Swigger
;Lab 5 assignment 9/15/2016

(defun add-only-numbers (x)
	(COND
	  ((NULL x) 0)
	  ((numberp (first x)) (+ (first x) (add-only-numbers (rest x))))
	  (T(add-only-numbers (rest x)))
	)
)

(defun remove-vowels (x)
	(COND
	  ((NULL x) nil)
	  ((member (first x) '(a e i o u)) (remove-vowels (rest x)))
	  (T (cons (first x) (remove-vowels (rest x))))
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

(defun destroyer (x y)
;x is a SORTED list of positions to destroy; y is a list
	(COND
	  ((NULL x) y)
	  ((listp x) (destroyer (first x) (destroyer (rest x) y)))
	  ((atom x) (remover x y))
	)
)
