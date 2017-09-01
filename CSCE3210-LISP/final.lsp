(defun f11 (x f)
        (cond ((null x) nil)
               ((atom x) (funcall f x))
               (t (append (f11 (rest x) f) (list (f11 (first x) f))))))
                 
(defun do-f11()
       (f11 '((1 2) 3 (4 5)) (lambda (x)(* x 11)))) 


(defun do-f13()
   (let* ((funls (list (lambda (x y)(+ x y))
                       (lambda (x y)(* x y))
                       (lambda (x y)(- x y))))
                  (as '(2 5 1))
                  (bs '(3 7 9)))
              (mapcar (lambda (a-fun a b) (funcall a-fun  a b))
                           funls  as  bs)))

;;adds the first two from a and b. 2 + 3. then multiplies the second two from a and b 5 * 7. then subtrascts the last two 1 - 9.
;;


(defun f14 (x)
        (lambda (y) (- x y)))
	(defun do-f14()
                   (funcall (f14 (funcall (f14 3) 2)) 7))

(defun do-15()
             (append ‘((a b))
              (cons (append ‘(1 2 ) nil)
                      (reverse (cons ‘((5 6)) (cons ‘(3 4) nil ))))))

(defun initialize ()
(setf my-array (make-array ‘(2 3):initial-contents ‘((a b c) (1 2 3)))))

(defun test (name)
   (let ((sum 0))
	(dotimes (c 2)
	(setf sum (+ sum (aref name 1 c))))
                    sum))

