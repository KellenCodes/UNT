;M Kellen Mills
;Symbolic Processing with Dr. Swigger

(defun countdown (x)
	(COND 
	  ((NULL x) nil)
	  ((= x 0) nil)
	  (t (cons x (countdown (- x 1))))
	)
)

(defun replicate (x foo)
	(COND
	  ((OR (NULL x) (NULL foo)) nil)
	  ((= x 0) nil)
	  (t (cons foo (replicate (- x 1) foo)))
	)
)

(defun double-each-element (x)
	(COND
	  ((NULL x) nil)
	  (t (cons (* 2 (first x)) (double-each-element (rest x))))
	)
)
