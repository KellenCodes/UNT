 (defun addwbranches (location wbranches)
	(setf (get location 'connected-to) wbranches))

(addwbranches 'denton  '((acity . 70) (bcity . 50)))
(addwbranches 'acity  '((ccity . 80) (dcity . 140)))
(addwbranches 'bcity '((ecity . 120)))
(addwbranches 'ccity '((fcity . 200)))
(addwbranches 'ecity  '((gcity . 70)( hcity . 120) (icity . 140)))
(addwbranches 'gcity '((jcity . 110) (kcity . 40)))
(addwbranches 'hcity '((lcity . 150) (mcity . 40)))
(addwbranches 'icity '((ncity . 20) (ocity . 50))) 


(defun expanpaths (path) 
          	(mapcar  (lambda (nextpath) (cons nextpath path)) 
                               (get (first (first path)) 'connected-to)))

 (defun match (element pattern)
 	     (equal element pattern)) 

	(defun cost (paths)
                  (let ((bestpath nil)
                         (temppath 0))
                     (setf bestpath (cons (apply '+ (mapcar 'rest (first paths))) (first paths)))
                     (setf paths (rest paths))
                     (loop
                      (if (null paths) (return (rest bestpath)))
                      (if (< (setf temppath (apply '+ (mapcar 'rest (first paths)))) (first bestpath))
                          (setf bestpath (cons temppath (first paths))))
                      (setf paths (rest paths)))))
(setq counter 0)

(defun cost-first (start goal)
   (let ((current  nil) (paths nil))
        (setq paths (list (list (cons start 0))))
        (loop
           (print 'paths) (princ paths)
           (print 'counter) (princ counter)
	   
           (setq current (cost  paths))
           (cond
                 ((null paths) (return nil))
                 ((match (first (first current)) goal)
                  (return (reverse current)))
                 (t (values (setq counter (+ counter 1))(setq paths (append
                     (remove current paths :test #'equal)
                     (expanpaths current)))))))))

