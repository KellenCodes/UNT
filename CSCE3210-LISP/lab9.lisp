;;M Kellen Mills, mostly copied from Dr. Swigger's code in the search-lab document
;;CSCE3210 Symbolic processing with Dr. Swigger

(defun addcity   (location branches)
   (setf (get location 'connected-to) branches))

(addcity 'denton '(acity  bcity))
(addcity 'acity  '(ccity dcity))
(addcity 'bcity '(ecity))
(addcity 'ccity '(fcity))
(addcity 'ecity  '(gcity hcity  icity))
(addcity 'gcity '(jcity kcity))
(addcity 'hcity '(lcity mcity))
(addcity 'icity '(ncity ocity))

(defun match (element pattern)
            (equal element pattern))

(defun expanpaths (path)
           (mapcar (lambda (nextpath) (cons nextpath path))
                 (get (car path) 'connected-to))) 

(defun depth-first (start goal)
;;this is the original function that I was given...with a counter
   (let* ((count 0)
	  (paths (list (list start)))
          (current paths))
     (loop
          (setq current (first paths))
		(print 'paths) (princ paths)
	    	(print 'current) (princ current)
            (cond  ((null paths) (return nil))
                        ((match (first current ) goal)
                           (return (values count (reverse current))))
                        (t (values (setq count (+ count 1)) (setq paths
                               (append (expanpaths current) (rest paths)))))))))

(defun breadth-first (start goal)
;;this is the function that uses breadth first.
   (let* ((count 0)
	  (paths (list (list start)))
          (current paths))
     (loop
          (setq current (first paths))
		(print 'paths) (princ count) (princ paths)
	    	(print 'current) (princ current)
            (cond  ((null paths) (return nil))
                        ((match (first current ) goal)
                           (return (values count (reverse current))))
                        (t (values (setq count (+ count 1)) (setq paths
                               (append (rest paths) (expanpaths current)))))))))
