;M kellen mills
;symbolic processing with Dr. Swigger

(defun subtract2 (numbers)
	(mapcar (lambda (number)
		  (- number 2))
	numbers))

(defun select (major year database)
	(remove nil (mapcar (lambda (data)
		  (COND ((equal major (second data)) (cons (first data) (list(- year (third data)))))
			))
	database)))
		
