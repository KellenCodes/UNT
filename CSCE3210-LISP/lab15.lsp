;;; Michael Kellen Mills -> lab 15 -> Hash table lab.
;;; Symbolic Processing with Dr. Swigger CSCE3210

(defun initialize ()
	(setf city
		 '((denton  ((acity . 70) (bcity . 50)))
		(acity  ((ccity . 80) (dcity . 140) (denton . 70)))
		(bcity ((ecity . 120) (denton . 50)))
		(ccity ((fcity . 200) (acity . 80)))
		(ecity ((bcity . 120)(gcity . 70)( hcity . 120) (icity . 140)))
		(gcity ((ecity . 70)(jcity . 110) (kcity . 40)))
		(hcity ((ecity . 120) (lcity . 150) (mcity . 40)))
		(icity ((ecity . 140) (ncity . 20) (ocity . 50)))))
	(setf my-hash (make-hash-table)))

(defun fill-city (city-hash city)
	(dolist (i city)
		(setf (gethash (first i) city-hash) (second  i))))

(defun get-neighbors (city-hash my-query)
	(gethash my-query city-hash))

(defun distance (from-city to-city)
	(rest (assoc to-city (get-neighbors my-hash from-city))))

(defun new-distance (from-city max-far)
	(mapcar (lambda (place)
		(cond ((>= max-far (rest place)) (list (first place))))
	) (gethash from-city my-hash) ))
