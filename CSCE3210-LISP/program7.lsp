;;M kellen Mills - program 7
;;symbolic processig with Dr. Swigger

(defun initialize ()
	(setf my-array
		(make-array '(3 3):initial-contents 
			'((" "  " "  " ")(" "  " "  " ")(" "  " "  " ")))))
(defun play ()
	(initialize)
	(setf player "o")
	(loop while (won my-array player) do
		(setf player (other-player player))
		(print "place your mark by typing something like (player-move player 2 2)")
		(print (list "it is now " player " turn."))
		(hard-code-board-print my-array)
		(print "")
		(setf message (read))
		(when (equal message 'quit) (return))
		(print (eval message))
	)
	(hard-code-board-print my-array)
	(print (list "Player " player "won the game! congrats!"))
)

(defun hard-code-board-print (my-array)
		(print (list (aref my-array 0 0) (aref my-array 1 0) (aref my-array 2 0)))
		(print (list (aref my-array 0 1) (aref my-array 1 1) (aref my-array 2 1)))
		(print (list (aref my-array 0 2) (aref my-array 1 2) (aref my-array 2 2)))
)

(defun player-move (player x y)
	(setf (aref my-array x y) player))

(defun won (board player)
	(cond ((or (vertical-line board player)
	    (horizontal-line board player)
	    (diagonal-up-line board player)
	    (diagonal-down-line board player)) nil)
	  (T T))
)

(defun other-player (player)
	(if (string-equal player "x") "o" "x"))

;;tests if the player who just placed a piece won a vertical
(defun vertical-line (board player)
	(loop for i from 0 to 2
		thereis(and (string-equal player (aref board 0 i))
		    (string-equal player (aref board 1 i))
		    (string-equal player (aref board 2 i))
		    )))
(defun horizontal-line (board player)
	(loop for i from 0 to 2
		thereis(and (string-equal player (aref board i 0))
		    (string-equal player (aref board i 1))
		    (string-equal player (aref board i 2))
		    )))
(defun diagonal-down-line (board player)
	(and (string-equal player (aref board 0 0))
	  (string-equal player (aref board 1 1))
	  (string-equal player (aref board 2 2))))
(defun diagonal-up-line (board player)
	(and (string-equal player (aref board 0 2))
	  (string-equal player (aref board 1 1))
	  (string-equal player (aref board 2 0))))

(defun test (type board player)
	(cond
	  ((equal type 'horz) (horizontal-line board player))
	  ((equal type 'vert) (vertical-line board player))
	  ((equal type 'diup) (diagonal-up-line board player))
	  ((equal type 'dido) (diagonal-down-line board player))))
(defun make-horz ()
	(setf my-horizontal
		(make-array '(3 3):initial-contents 
			'(("x"  "x"  "x")(" "  " "  " ")(" "  " "  " ")))))
(defun make-vert ()
	(setf my-vertical
		(make-array '(3 3):initial-contents 
			'(("x"  " "  " ")("x"  " "  " ")("x"  " "  " ")))))
(defun make-dido ()
	(setf my-dido
		(make-array '(3 3):initial-contents 
			'(("x"  " "  " ")(" "  "x"  " ")(" "  " "  "x")))))
(defun make-diup ()
	(setf my-diup
		(make-array '(3 3):initial-contents 
			'((" "  " "  "x")(" "  "x"  " ")("x"  " "  " ")))))
