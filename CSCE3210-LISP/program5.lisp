;;;Michael Kellen Mills
;;; CSCE3210 -- symbolic processing with Dr. Swigger

(defun initialize ()
	(setf water-node '((1 0) (2 0) (3 0) (4 0) (5 0) (6 0) (7 0) (5 4) (5 5) (5 6) (5 7)))
	(setf pit-node '((6 1) (1 5)))
	(setf goal-node '((4 2) (3 5) (7 6)))
	(set-max)
)

(defun next-nodes (path)
	(cond ((listp (first (last path))) (setf new-nodes (clean (generate (first (last path))))))
		(T (setf new-nodes (clean (generate path))))
	)
)

(defun propogate-next-move (path-matrix)
	(mapcar (lambda (each-path)
		(setf to-add (next-nodes each-path))
		(cons (add-node-onto each-path (first to-add)) (add-node-onto each-path (rest to-add)))
	) path-matrix)
)

(defun add-node-onto (x-list y-node)
	(cond
	  ((null y-node) nil)
	  ((listp (first y-node)) (cons (add-node-onto x-list (first y-node)) (add-node-onto x-list (rest y-node))))
	  (T 
		(cond 
			((is-that-list-in-this-huge-list y-node x-list) x-list)
			(T (append x-list (list y-node))))))
)

(defun is-that-list-in-this-huge-list (y-node x-list)
	(setf it-is nil)
	(mapcar (lambda (node)
		(cond ((equal y-node node) (setf it-is T)))
	) x-list)
	(cond (it-is T))
)

;(defun expand (paths)
;	(setf this-new-path nil)
;	(cond ((null paths) nil)
;		((listp (first paths)) (cons (expand (first paths)) (expand (rest paths))))
;		(T (setf new-nodes (clean (generate paths)))
;			(setf old-path paths)
;			(mapcar (lambda (add-node)
;				(setf this-new-path (list this-new-path (list old-path add-node)))
;			) new-nodes)
;		))
;	(setf this-new-path (recurse-remove nil this-new-path))
;)


(defun set-max ()
	(setf max-x 0)
	(setf max-y 0)
	(mapcar (lambda (node)
		(cond
			((> (first node) max-y) (setf max-y (first node))))
		(cond
			((> (second node) max-x) (setf max-x (second node))))
	) water-node)
	(mapcar (lambda (node)
		(cond
			((> (first node) max-y) (setf max-y (first node))))
		(cond
			((> (second node) max-x) (setf max-x (second node))))
	) pit-node)
	(mapcar (lambda (node)
		(cond
			((> (first node) max-y) (setf max-y (first node))))
		(cond
			((> (second node) max-x) (setf max-x (second node))))
	) goal-node)
)

(defun generate (x)
;generate works like: (generate '(0 0))-->((1 0) (-1 0) (0 1) (0 -1))
;;;;	(cond ((listp (first x)) (setf x (last x))))
	(list
	  (list (+ (first x) 1) (first (rest x)))
	  (list (- (first x) 1) (first (rest x)))
	  (list (first x) (+ (first (rest x)) 1))
	  (list (first x) (- (first (rest x)) 1))))

(defun clean (x)
;clean works like: (clean (generate '(0 0))) --> ((1 0) (0 1))
	(mapcar (lambda (node) 
		(cond 
			((has-neg node)(setf x (remove node x)))
		)
	) x)
	(print x))


(defun has-neg (node)
	(cond 
		((> 0 (first node)) T)
		((> 0 (second node)) T)
		((< max-y (first node)) T)
		((< max-x (second node)) T)
		(T nil)))
(defun recurse-remove (y x)
        (cond
          ((null x) nil)
          ((atom x)
            (cond
              ((equal x y) nil)
              (T x)))
          (T (remove nil (cons (delete y (first x)) (delete y (rest x)))))))

;(defun normalize (matrix)
;	(cond ((null matrix) nil)
;		((listp (first (first (first matrix)))) (first matrix)
