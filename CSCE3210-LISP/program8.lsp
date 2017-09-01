;;M. Kellen Mills -- program8.lsp 
;; Q-learning in grid world!
;; CSCE3210 - Symbolic processing with Dr. Swigger!
;;University of North Texas

;;makes arrays and discount amount for rewards close to the finish line.
(defun initialize ()
	(setf gamma .5)  ; this is my discount value
	(setf r-array (make-array '(64 4) :initial-element 0))
	(setf q-array (make-array '(64 4) :initial-element 0))
	(initialize-r)
)
;;this is here for completeness...
(defun print-array (array) ;; and a print-array when you need it
   (dotimes (row 64)
     (dotimes (column 4)
       (princ (aref array row column)) (princ " "))
     (print "")
   ))
;;places values in the reward array
(defun initialize-r ()
   ;;if you are in state 61 and you move right, you are rewarded with 100.
   (setf (aref r-array 8 0 ) NIL)
   (setf (aref r-array 16 0) NIL)
   (setf (aref r-array 24 0) NIL)
   (setf (aref r-array 32 0) NIL)
   (setf (aref r-array 40 0) NIL)
   (setf (aref r-array 48 0) NIL)
   (setf (aref r-array 56 0) NIL)
   (setf (aref r-array 56 2) NIL)
   (setf (aref r-array 57 2) NIL)
   (setf (aref r-array 58 2) NIL)
   (setf (aref r-array 59 2) NIL)
   (setf (aref r-array 60 2) NIL)
   (setf (aref r-array 61 2) NIL)
   (setf (aref r-array 62 2) NIL)
   (setf (aref r-array 63 2) NIL)
   (setf (aref r-array 63 1) NIL)
   (setf (aref r-array 55 1) NIL)
   (setf (aref r-array 47 1) NIL)
   (setf (aref r-array 39 1) NIL)
   (setf (aref r-array 31 1) NIL)
   (setf (aref r-array 23 1) NIL)
   (setf (aref r-array 15 1) NIL)
   (setf (aref r-array 7 1 ) NIL)
   (setf (aref r-array 7 3 ) NIL)
   (setf (aref r-array 6 3 ) NIL)
   (setf (aref r-array 5 3 ) NIL)
   (setf (aref r-array 4 3 ) NIL)
   (setf (aref r-array 3 3 ) NIL)
   (setf (aref r-array 2 3 ) NIL)
   (setf (aref r-array 1 3 ) NIL)
   (setf (aref r-array 0 3 ) NIL)
   (setf (aref r-array 0 0 ) NIL)

   (setf (aref r-array 61 1) 100)
   (setf (aref r-array 54 2) 100)
   (setf (aref r-array 63 0) 100)

   (setf (aref r-array 5 2 ) -5)
   (setf (aref r-array 12 1) -5)
   (setf (aref r-array 21 3) -5)
   (setf (aref r-array 14 0) -5)

   (setf (aref r-array 41 2) -5)
   (setf (aref r-array 48 1) -5)
   (setf (aref r-array 50 0) -5)
   (setf (aref r-array 57 3) -5)

   (setf (aref r-array 0 2 ) -1)
   (setf (aref r-array 8 2 ) -1)
   (setf (aref r-array 16 2) -1)
   (setf (aref r-array 32 3) -1)
   (setf (aref r-array 52 3) -1)
   (setf (aref r-array 53 3) -1)
   (setf (aref r-array 54 3) -1)
   (setf (aref r-array 55 3) -1)
   (setf (aref r-array 36 2) -1)
   (setf (aref r-array 37 2) -1)
   (setf (aref r-array 38 2) -1)
   (setf (aref r-array 39 2) -1)
   (setf (aref r-array 57 0) -1)
   (setf (aref r-array 49 0) -1)
   (setf (aref r-array 41 0) -1)
   (setf (aref r-array 33 0) -1)
   (setf (aref r-array 25 0) -1)
   (setf (aref r-array 17 0) -1)
   (setf (aref r-array 9 0 ) -1)
   (setf (aref r-array 32 2) -1)
   (setf (aref r-array 24 2) -1)
   (setf (aref r-array 40 2) -1)
   (setf (aref r-array 48 2) -1)
   (setf (aref r-array 56 3) -1)
   (setf (aref r-array 16 3) -1)
   (setf (aref r-array 32 3) -1)
   (setf (aref r-array 40 3) -1)
   (setf (aref r-array 48 3) -1)
   (setf (aref r-array 24 3) -1)
   (setf (aref r-array 47 0) -1)
   (setf (aref r-array 46 0) -1)
   (setf (aref r-array 45 0) -1)
   (setf (aref r-array 44 0) -1)
   (setf (aref r-array 43 1) -1)
   (setf (aref r-array 46 1) -1)
   (setf (aref r-array 45 1) -1)
   (setf (aref r-array 44 1) -1)
)

;;;moves to the goal, given a starting point;;;
(defun q-learning (start)
    (setf current-state start)
    
    ;;;repeat the following until you find the goal;;;
    (loop while (not (eq current-state 62)) do
	(setf next-action (q-next-action current-state))
	(princ "(")
	(princ current-state) (princ ", ")
	(print-action next-action) (princ " -> ")

	(setf current-state (move-to current-state next-action))
    )
	(princ current-state)
)

(defun print-action (act-now)
	(if (eq 0 act-now) (princ "left)"))
	(if (eq 1 act-now) (princ "right)"))
	(if (eq 2 act-now) (princ "up)"))
	(if (eq 3 act-now) (princ "down)"))
)

(defun q-next-action (state)
	(setf max-q (examine-q state))
	(if (eq max-q (aref q-array state 0))
		(setf action-q 0)) 

	(if (eq max-q (aref q-array state 1))
		(setf action-q 1))

	(if (eq max-q (aref q-array state 2))
		(setf action-q 2))

	(if (eq max-q (aref q-array state 3)) 
		(setf action-q 3))
	action-q
)
;;;finds all the Q-values for the given grid;;;
(defun q-values ()
	;;;1000 surveys is enough;;;
	(setf x 1000)
	(loop while (>= x 0) do
		(q-episode)
		(setf x (- x 1)))
)

(defun q-episode ()
    (setf current-state (random 64))
    ;;;repeat the following until you find the goal;;;
    (loop while (not (eq current-state 62)) do

	;;;select a random action;;;
	(setf next-action (random 4))

	;;;check if that random action puts us out-of-bounds;;;
	(loop while (not (aref r-array current-state next-action)) do
	    ;;;if it did, pick a new one and try again;;;
	    (setf next-action (random 4)))
	;;;with your randomly selected state, set a variable equal to the new state;;;
	(setf next-state (move-to current-state next-action))
	(setf (aref q-array current-state next-action) 
		(+ (aref r-array current-state next-action) (* gamma (examine-q next-state))))
	(setf current-state next-state)
    )
)

(defun examine-q (state)
	(setf max-q 0)
	(if (< max-q (aref q-array state 0)) (setf max-q (aref q-array state 0)))
	(if (< max-q (aref q-array state 1)) (setf max-q (aref q-array state 1)))
	(if (< max-q (aref q-array state 2)) (setf max-q (aref q-array state 2)))
	(if (< max-q (aref q-array state 3)) (setf max-q (aref q-array state 3)))
	max-q
)

;; 2->up::add 8
;; 3->down::subtract 8
;; 1->right::add 1
;; 0->left::subtract 1
(defun move-to (state action)
	(cond
		((eq action 0) (- state 1))
		((eq action 1) (+ state 1))
		((eq action 2) (+ state 8))
		((eq action 3) (- state 8))
	)
)
