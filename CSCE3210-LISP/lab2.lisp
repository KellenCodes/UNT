;;M. Kellen Mills
;; Lab 2, symbolic processing

(defun first-one (A)
	(first A))
(defun my-new-list (B)
	(CONS (first (rest B)) (first (rest (rest B)))))
(defun my-adder (C)
	(+ 10 (first C)))
