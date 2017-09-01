(defun initialize ()
    (setf gold '((2 2)))
    (setf hole '((2 1)))
    (setf water '((0 0)(1 0)(2 0))))

(defun generate (x)
;generate works like: (generate '(0 0))-->((1 0) (-1 0) (0 1) (0 -1))
        (list
          (list (+ (first x) 1) (first (rest x)))
          (list (- (first x) 1) (first (rest x)))
          (list (first x) (+ (first (rest x)) 1))
          (list (first x) (- (first (rest x)) 1))))
(defun allow-extension (x)
	(cond
	((listp (first (rest x))) (list (allow-extension (first x)) (allow-extension (rest x))))
	((member -1 x) nil)
	(T(list (first x) (rest x)))))

(defun match (element pattern)
            (equal element pattern))

(defun expanpaths (path)
           (mapcar (lambda (nextpath) (cons nextpath path))   
                 (get (first path) 'connected-to)))  
	
(defun breadth-first (start goal)
   (let* ((paths (list (list start)))
          (current paths)
          (counter 0))
     (loop
          (setq current (first paths))
              (cond  ((null paths) (return nil))
                        ((match (first current ) goal)
                           (return (cons counter (reverse current))))
                        (t (setq paths
                                (append  (rest paths)(expanpaths current)))
                           (setq counter (+ counter 1))))))) 

