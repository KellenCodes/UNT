;;M Kellen Mills
;;Symbolic Processing with Dr. Swigger -- CSCE3210

(defun initialize ()
		(setf john (make-person 'john 'secretary 30 'companyx))
		(setf june (make-person 'june 'manager  nil 'companyx))
		(setf companyz (make-company 'companyz '(free-WiFi free-parking corporate-housing) nil))
		(setf companyx (make-company 'companyx 'free-parking '(june john))))

(defun make-person (name job age company)
	(lambda (message)
	      (cond ((equal message 'name) name)
	        ((equal message 'job) job)
                ((equal message 'age) age)
  	        ((equal message 'work-for)company)
	        ((equal message 'company)company)
		((equal message 'move) 
                  (lambda (newcompany)
                    (send (eval company) 'delete-emp name)
                      (setq company newcompany)
      		    (send (eval company) 'add-emp name)))
		((equal message 'perks)
      		  (let ((perks nil))
	            (if (equal job 'manager) (setf perks (cons 'car perks)))
	              (setf perks (cons (ask (eval company) 'perks) perks)))))))

(defun make-company (name perks employee-list)
     (lambda (message)
	(cond ((equal message 'name)name)
          ((equal message 'perks) perks)
	  ((equal message 'employee-list) employee-list)
	  ((equal message 'add-emp) 
	    (lambda (emp)
	      (setf employee-list (cons emp employee-list))))
	  ((equal message 'delete-emp)
            (lambda (emp)
              (setf employee-list (delete emp employee-list))))
	  ((equal message 'employee) 
            (lambda (arg)
              (let ((emp arg)) 
                 (if (equal (ask (eval emp) 'work-for) name)
                   (print "yes") (print "no"))))))))


(defun ask (object message)
     (funcall object message))

(defun send (object message &rest args)
	(apply (ask object message) args))

