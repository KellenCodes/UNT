;; M Kellen Mills -- mkm0222
;; Symbolic Processing with Dr. Swigger
;; Bayesian Network Lab

(setf *test-net*
      '((Cause (true false)          		; can take on values true/false
	       ()                    		; has no parents
	       (0.98 0.02))           		 ; P(Cause = true) = P(Cause = false) = 0.5
	(Effect1 (true false)       
		 (Cause)             	; has Cause as its only parent
		 ((true) 0.7 0.3)    	; these 4 numbers represent the CPT
		 ((false) 0.5 0.5))  	; (note that each row adds up to 1)
	(Effect2 (true false)
		 (Effect1)
		 ((true) 0.8 0.2)    
		 ((false) 0.4 0.6)
        
      )))

;; Given a bayes net, this code 
;;are you reading this?
;; returns a list of vars where parents always appear before their children
(defun topological-sort-vars (bn)
  (let* ((topology (get-vars-with-parents bn))
	 (ordered-nodes nil))
    (loop
     (if (null topology) (return (reverse ordered-nodes)))
     (dolist (node-data topology)
       (let ((node (first node-data))
	     (node-parents (rest node-data)))
	 (if (null node-parents)
	     (progn
	       (push node ordered-nodes)
	       (setf topology
		     (remove nil
			     (mapcar #'(lambda (l) (remove node l))
				     topology)))
	       (return))))))))

(defun get-vars (bn)
  (mapcar #'first bn))

;;;This function gets the values (true, false) for a particular variable
(defun get-values (var bn)
  (second (assoc var bn)))

; This function returns the parents (or nil) for a particular variable
(defun get-parents (var bn)
  (third (assoc var bn)))

(defun get-cpt (var bn)
  (nthcdr 3 (assoc var bn)))

(defun get-all-parents (bn)
  (mapcar #'third bn))

(defun get-vars-with-parents (bn)
  (let ((vars (get-vars bn))
	(parents (get-all-parents bn)))
    (mapcar #'cons vars parents)))

;; This function returns a SPECIFIC cpt value, given a variable, a value for that variable, and a list of current variables & values.  
;; assumes all parents have values specified in vars-with-vals
(defun prob-given-parents (var val vars-with-vals bn)
  (let* ((var-data (rest (assoc var bn)))
	 (column (position val (get-values var bn)))
	 (parents (second var-data))
	 (parent-vals (list-vals-for parents vars-with-vals))
	 (cpt (nthcdr 2 var-data))
	 (cpt-row (if (null (rest cpt)) ; if only one row
		      (first cpt)       ; return it, else find matching row
		      (rest (assoc parent-vals cpt :test #'equal))))
	 )
      (nth column cpt-row)
    ))

;; look up values for the given vars and list them in same order
;; - used as a helper to access appropriate CPT values
(defun list-vals-for (vars vars-with-vals)
  (if (null vars)
      nil
      (cons (second (assoc (first vars) vars-with-vals))
	    (list-vals-for (rest vars) vars-with-vals))))

;; vars-with-vals is a list of the form ((var-1 val-1) ... (var-n val-n))
;; returns nil if var doesn't appear in vars-with-vals
(defun get-val (var vars-with-vals)
  (let ((var-val-pair (assoc var vars-with-vals)))
    (if var-val-pair (second var-val-pair) nil)))
