; M. Kellen Mills
; Symbolic processing with Dr. Swigger

(defun where-is (x)
	(first (member 'waldo x))
)

(defun gross-receipts (x y)
	(+ (* x 7) (* y 4))
)

(defun longer-list (x y)
	(COND 
		((OR (NULL x) (atom x)) '(first element is not a list))
		((OR (NULL y) (atom y)) '(second element is not a list))		
		((append x y))
	)
)

(defun between (x y z)
	(COND
		((AND (< x y z) (> z y x)) 't)
		((AND (< z y x) (> x y z)) 't)
		('nil)
	)
)

(defun triangle (x y z)
	(COND
		((AND (>= (+ x y) z) (>= (+ x z) y) (>= (+ y z) x)))
	)
)
