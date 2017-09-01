

;; Main program.  Assumes that query-var is not among the evidence
;; variables (but it could be modified easily to handle this possibility).
;; It could also be modified (with somewhat more effort) to return a
;; joint conditional distribution given a list of query variables.
;; 
;; The "evidence" input is assumed to be a list of variable/value pairs
;; (2-element lists, not dotted pairs).
;;
;; The returned value has the form ((val-1 prob-1) ... (val-n prob-1)),
;; where n is the number of different values the query variable can take on.
;;
#| Sample call:

(query-by-enumeration 'Cause '((Effect2 true))
		      *test-net*)

|#

(defun query-by-enumeration (query-var evidence bn)
  (let* ((vals (get-values query-var bn))
	 (sorted-vars (topological-sort-vars bn))
	 (distribution nil))
	 (print 'vals)(princ vals)(print 'sorted)(princ sorted-vars)
    (dolist (val vals (normalize (reverse distribution)))
     (print 'inside-query-enumeration)
      (push (list val
		  (enumerate-all sorted-vars
				 (cons (list query-var val) evidence)
				 bn))
	    distribution))
    ))

(defun enumerate-all (vars vars-with-vals bn) 
  (print 'in-enumerate)
  (print 'vars) (princ vars)
  (print 'vars-with-vals)(princ vars-with-vals)
  (if (null vars)
      1.0
      (let* ((var (first vars))
	     (val (second (assoc var vars-with-vals))))
	(if val
	    (and (print t) (* (prob-given-parents var val vars-with-vals bn)
	                   (enumerate-all (rest vars) vars-with-vals bn)))
	    (let ((sum 0.0)
		  (vals (get-values var bn)))
	      (dolist (val vals sum)
                 (print 'val)(princ val)(print 'var)(princ var)
		(let ((new-vars-vals (cons (list var val) vars-with-vals)))
                   (print 'new-vars-vals) (princ new-vars-vals)
                  
		  (and (incf sum (* (prob-given-parents var val vars-with-vals bn)
			       (enumerate-all (rest vars)
					      new-vars-vals
					      bn))) (print 'sum2)(print sum)))
	    ))))))

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

;; a distribution is assumed to be a list of elements having the form
;; (symbol-1 ... symbol-k number), which specifies the relative probability
;; of each particular combination of values for k query variables
(defun normalize (distrib)
  (let* ((nums (mapcar #'(lambda (l) (first (last l))) distrib))
	 (probs (normalize-nums nums))
	 (val-combos (mapcar #'butlast distrib)))
    (mapcar #'(lambda (l n) (append l (list n))) val-combos probs)))

(defun normalize-nums (alon)
  (let ((sum (apply #'+ alon)))
    (mapcar #'(lambda (x) (/ x sum)) alon)))

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; These utilities are directly dependent on the details of the
;;; Bayes net data structure.  To see how a Bayes net is assumed to be
;;; encoded, look at "test-net.lisp" ; for example.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun get-vars (bn)
  (mapcar #'first bn))

(defun get-values (var bn)
  (second (assoc var bn)))

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
      (print 'inside-prob-parents)(princ parents)
      (print 'cpt-row)
      (print (nth column cpt-row))
      (nth column cpt-row)
    ))
(setf *test-net*
      '((Cause (true false)          ; can take on values true/false
	       ()                    ; has no parents
	       (0.98 0.02))            ; P(Cause = true) = P(Cause = false) = 0.5
	(Effect1 (true false)       
		 (Cause)             ; has Cause as its only parent
		 ((true) 0.2 0.8)    ; these 4 numbers represent the CPT
		 ((false) 0.7 0.3))  ; (note that each row adds up to 1)
	(Effect2 (true false)
		 (Effect1)
		 ((true) 0.8 0.2)    
		 ((false) 0.5 0.6)
        
      )))
