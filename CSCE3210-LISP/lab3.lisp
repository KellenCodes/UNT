;; M Kellen Mills
;; CSCE3210 Symbolic Processing w/ Dr. Swigger

(defun data-type (x)
	(cond ((numberp x) 'number)
		((atom x) 'atom)
		((listp x) 'list)
	)
)

(defun report-victory (x)
	(cond ((> x 0) 'I-WON)
		((< x 0) 'YOU-WON)
		((= x 0) 'TIE)
	)
)

(defun asc-sqr (a b c)
	(cond ((= b (* a a)) 'square)
		((= a (+ b c)) 'times)
		(T 'nothing)
	)
)
