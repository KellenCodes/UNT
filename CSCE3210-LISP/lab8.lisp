;M. Kellen Mills
;Symbolic Processing with Dr. Swigger

(setf car-list nil)

(defun make-models (car money)
  (setf (get car 'cost) money)
  (setf car-list (cons car car-list)))

(defun create ()
  (make-models 'toyota 30000)
  (make-models 'ford-fusion 27000)
  (make-models 'jeremy 36000)
  (make-models 'franklin 80000)
  (make-models 'mercedes 50000)
  (make-models 'ugo 27500)
  (make-models 'nova 29000)
  (make-models 'jetta 29990)
  (make-models 'Hagen-das 32000)
  (make-models 'pickle-wagon 39900))

(defun model-grabber (car-list cost)
	(COND
	  ((equal cost (get (first car-list) 'cost)) (first car-list))
	  (T(model-grabber (rest car-list) cost))
	)
)
(defun get-cost (car-list)

	;this blob returns to cost. not the model...
	(COND
	  ((null (rest car-list)) (get (first car-list) 'cost))
	  (T
	    (cond 
	      ((< (get (first car-list) 'cost) (get-cost (rest car-list))) (get (first car-list) 'cost))
	      (T(get-cost (rest car-list)))
	    )
	  )
	)
)
	  
(defun get-cheapest (car-list)
	(model-grabber car-list (get-cost car-list))
)
