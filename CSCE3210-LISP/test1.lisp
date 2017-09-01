(defun find-price (want stock)
	(cond
		((listp want) (+ (find-price (first want) stock)(find-price (rest want) stock)))
		(T(dolist(x stock (cond
					((member want x) rest x))
					(T( 0))))))))
