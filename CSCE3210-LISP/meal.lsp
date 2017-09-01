(defun fill-menu (htable lis)
	(dolist (x lis)
	    (setf (gethash (first x) htable) (second x))))
(defun init ()
(setf my-menu (make-hash-table))
(fill-menu my-menu
(setf menu '((meal  ((hamburger pizza chicken)))
(hamburger  (fries malt)) 
(pizza (breadsticks coke))
(chicken (potatoes coffee))
(fries (ice-cream cake))
(potatoes (pie))
(breadsticks (brownie))))))


(defun my-meal (entre hasbl)
                   (let ((temp (gethash entre hasbl))
                       (new-list entre))
                      (loop
                       (if (equal temp nil) (return new-list)
                         (progn 
                           (setf new-list (cons temp new-list))
                           (setf temp (gethash (first temp) hasbl)))))))

