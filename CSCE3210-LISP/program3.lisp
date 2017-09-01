;m kellen mills
; symbolic processing with Dr. Swigger
;Program 3 - More recursion

(defun my-replace (x y)
	(COND
	  ((NULL x) nil)
	  (T 
	    (CONS 
	      (COND
		((EQUAL (first x) (first y)) (first (rest y))) ;If the atoms match, CONS replacement
		(T (first x)) 				   ;or if the atoms don't match, CONS original
	      )
	      (my-replace (rest x) y) ;second argument given to CONS
	      )
	    )
	  )
)

(defun add-lists (x y)
      (COND
	((NULL x) y )
	((NULL y) x )
        (T (CONS (+ (first x) (first y)) (add-lists (rest x) (rest y))) ) ;IF YOU ARE HERE< I want you to smash together the sum and call on yourself again.
      )
)

(defun select (maj yr data)
	(convert maj yr (my-trim maj yr data))
)

(defun convert (maj yr data)
;Takes what it can get and converts it to the ascribed format.
	(COND
	  ((NULL data) nil)
	  ((cons (cons (first (first data)) (- yr  (third (first data))) ) (convert maj yr (rest data))))
	)
)
(defun my-trim (maj yr data)
;finds students
	(COND
	  ((NULL data) nil)
	  ((COND
	    ((member maj (first data)) (CONS (first data) (my-trim maj yr (rest data))) )
	    (T (my-trim maj yr (rest data)))
	  ))
	)
)
