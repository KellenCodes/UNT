;M. Kellen Mills
;Symbolic processing with Dr. Swigger.

(defun remove-vowels (x)
;removes vowels from the list (x)
	(let ((y nil))
	  (dolist (ele x (reverse y))
	    (COND
	      ((member ele '(a e i o u)) nil)
	      (T(setq y (cons ele y)))
	    )
	  )
	)
)

(defun replicate (x y)
;creates a list of x number of y's
	(let ((n 0) (replis nil))
	  (loop
	    (if (equal n x) (return replis)
	      (setf replis (cons y replis)))
		(setf n (+ n 1))
	  )
	)
)

(defun add-only-numbers (x)
;x is a complicated list of junk to have its numbers added
	(let ((y 0) (z 0))
	  (dolist (ele x y)
	    (COND
	      ((numberp ele)
	      (setf y (+ y ele)))
	      ((listp ele)
		(dolist (elm ele z)
		  (if (numberp ele)
		  (setf y (+y elm)))
		)
	      )
	    )
	  )
	)
)
