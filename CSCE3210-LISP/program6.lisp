;;M Kellen Mills 	michaelmills5@my.unt.edu
;;symbolic processing with Dr. Swigger

(defun initialize ()
	(setf time 120)
	(setf bank (make-building 'bank '(union) '(money5)))
	(setf union (make-building 'union '(dormitory bank) '(albert food)))
	(setf library (make-building 'library '(computer-lab) '(swigger joke-book)))
	(setf computer-lab (make-building 'computer-lab '(english library) '(mary computer)))
	(setf dormitory (make-building 'dormitory '(english union) '(player bed shower)))
	(setf english (make-building 'english '(dormitory computer-lab) '(garbage lost-dreams)))

	(setf mary (make-person 'mary 'computer-lab '(mary-ID)))
	(setf albert (make-person 'albert 'union '(money1 albert-ID)))
	(setf swigger (make-person 'swigger 'library '(knowledge)))
	(setf player (make-person 'player 'dormitory '(dorm-key money1 player-ID)))
	
	(setf money1 (make-possession 'money1 'currency 'buy-food))
	(setf money5 (make-possession 'money5 'currency 'buy-tutoring))
	(setf player-ID (make-possession 'player-ID 'ID-card 'access-player))
	(setf mary-ID (make-possession 'mary-ID 'ID-card 'access-mary))
	(setf albert-ID (make-possession 'albert-ID 'ID-card 'access-albert))
	(setf knowledge (make-possession 'knowledge 'metaphor 'pass-assignment))
	(setf dorm-key (make-possession 'dorm-key 'bedroom-key 'unlock-sleeping))
	(setf food (make-possession 'food 'nourishment 'energize-brain))
	(setf joke-book (make-possession 'joke-book 'entertainment 'passing-time))
	(setf bed (make-possession 'bed 'essential 'restores-sanity))
	(setf computer (make-possession 'computer 'info-machine 'make-homework))
	(setf garbage (make-possession 'garbage 'trash 'make-smelly))
	(setf shower (make-possession 'shower 'water-works 'make-clean))
	(setf lost-dreams (make-possession 'lost-dreams 'social-construct 'make-depression))
	(funcall (driver)))

(defun make-person (name location possessions)
	(lambda (message)
	      (cond ((equal message 'name) name)
		        ((equal message 'location) location)
                        ((equal message 'possessions) possessions)

			((equal message 'move-to)
			  (lambda (newplace)
			    (cond 
			      ((member newplace (ask (eval location) 'neighbors))
			        (send (eval location) 'delete-possession name)
			        (setf location newplace)
			        (send (eval location) 'add-possession name)
			        (list name " is now in " newplace))
			    (T(list name " cannot move to " newplace " because that is not nearby.")))))

			((equal message 'look-around)
			  (list "indoors " (ask (eval location) 'possessions) "outside " (ask (eval location) 'neighbors)))

			((equal message 'drop)
			  (lambda (possession)
			    (setf possessions (delete possession possessions))
			    (send (eval location) 'add-possession possession)))

			((equal message 'add-possession)
			  (lambda (possession)
			    (setf possessions (cons possession possessions))))

			((equal message 'take)
			  (lambda (item)
			    (cond ((member item (ask (eval location) 'possessions))
			        (cond ((ask (eval item) 'possession)
			            (send (eval location) 'delete-possession item)
			            (send (eval name) 'add-possession item)
				    (list name " now has " item))
				  (T (list "that is not a possession!"))))
			      (T(list "That item isn't here.")))))

			((equal message 'submit)
			  (cond ((member 'computer possessions) 
				  (cond ((member 'swigger (ask (eval location) 'possessions))
					(print "you have turned in your homework! You have an A!")
					(setf time -1)
					(list "type quit to quit game"))
				    (T(list "Dr. Swigger is not in this building!"))))
				(T(list "you do not have a computer!"))))

			((equal message 'person) T)
)))

(defun make-building (name neighbors possessions)
	(lambda (message)
		(cond ((equal message 'name) name)
			((equal message 'neighbors) neighbors)
			((equal message 'possessions) possessions)
			((equal message 'add-possession)
			  (lambda (possession)
			    (setf possessions (cons possession possessions))))
			((equal message 'delete-possession)
			  (lambda (possession)
			    (setf possessions (delete possession possessions))))
			((equal message 'building) T)
)))

(defun make-possession (name type use)
	(lambda (message)
		(cond ((equal message 'name) name)
			((equal message 'type) type)
			((equal message 'use) use)
			((equal message 'possession) T)
)))

(defun ask (object message)
	(funcall object message))

(defun send (object message args)
	(funcall (ask object message) args))

(defun move-to (object message)
	(funcall (send object 'move-to message)))

(defun is-the-player-there (object)
	(cond ((member 'player (ask object 'possessions)) T)
		(T nil)))
(defun driver ()
   (loop
	(when (equal time -1) (return))
	(print "homework due at midnight")
	(print (list "now you have " time " minutes until midnight" ))
       (print "type (send player '<command> '<item/action>) commands: move-to, take, drop. item: (ask player '<possessions/look-around>)")
       (print "type (ask player '<action/question>) actions: look-around, submit. questions: name, location, possessions")
       (print "") 
       (setf message (read))
	(setf time (- time 6))
	(when (equal time 0) (print "You ran out of time! See you next semester!") (return))
       (when (equal message 'quit) (return)) 
      (print (eval message))
))  
