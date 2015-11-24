(define nil (quote ()))
(define error (quote error))

(define + (lambda (x y) (+ x y)))
(define - (lambda (x y) (- x y)))
(define * (lambda (x y) (* x y)))
(define cadr (lambda (x) (car (cdr x))))
(define print (lambda (x) (print x)))
(define car (lambda (x) (apply car (list x))))
(define cdr (lambda (x) (apply cdr (list x))))
(define cons (lambda (_car _cdr) (apply cons (list _car _cdr))))
(define ceiling (lambda (x) (ceiling x)))
(define floor (lambda (x) (floor x)))
(define < (lambda (x y) (< x y)))

(define list (lambda args
	       (if (not (nullp args))
                   (cons (car args) (cdr args))
		   nil)))
(define even? (lambda (x) (if (- x (* (/ x 2) 2)) 0 1)))

(define > (lambda (x y) (< y x)))
(define >= (lambda (x y) (not (< x y))))
(define <= (lambda (x y) (not (< y x))))
(define = (lambda (x y) (if (< x y) 0 (not (< y x)))))
(define != (lambda (x y) (not (= x y))))
(define and (lambda (x y) (if x (if y 1 0) 0)))
(define or (lambda (x y) (not (and (not x) (not y)))))
(define abs (lambda (x) (if (< x 0) (- 0 x) x)))
(define max (lambda (x y) (if (< x y) y x)))
(define min (lambda (x y) (if (< x y) x y)))
(define factorial (lambda (x) (if (< x 2) 1 (* x (factorial (- x 1))))))
(define square (lambda (x) (print (* x x)) (* x x)))
(define begin (lambda args (end args)))
(define append (lambda (list1 list2)
		 (if (nullp list1)
		     list2
		     (if (nullp (cdr list1))
			 (cons (car list1) list2)
			 (cons (car list1) (append (cdr list1) list2))))))
(define _map (lambda (func _list)
	      	   (if (not (nullp _list))
		       (if (nullp (cdr _list))
			     (cons (func (car _list)) nil)
		             (cons (func (car _list)) (_map func (cdr _list))))
		       nil)))
(define first (lambda args (car args)))
(define length (lambda (_list)
		 (if (nullp _list)
		     0
                     (+ 1 (length (cdr _list))))))

(define end (lambda (_list)
	       (if (not (nullp _list))
		   (if (not (nullp (cdr _list)))
		       (end (cdr _list))
		       (car _list))
		   nil)))

(define for-each (lambda args
		   (let ((func (car args)) (_list (cdr args)))
		     (if (not (listp (car _list)))
			 error
			 (if (not (nullp (car _list)))
			     (begin
			       (apply func (_map car _list))
			       (if (not (nullp (cdr (car _list))))
				   (eval (cons (quote for-each)
					       (cons func
						     (_map (lambda (x) (list (quote quote) (cdr x))) _list))))
				   nil))
			     nil)))))

(define map (lambda args
	      (let ((func (car args)) (_list (cdr args)))
		(if (not (listp (car _list)))
		    error
		    (if (not (nullp (car _list)))
			(if (nullp (cdr (car _list)))
			    (cons (apply func (_map car _list))
				  nil)
			    (cons (apply func (_map car _list))
				  (eval (cons (quote map)
					      (cons func
						    (_map (lambda (x) (list (quote quote) (cdr x))) _list))))))
			nil)))))
(define list-head (lambda (_list k)
		    (if (< k 0)
			error
			(if k
			    (cons (car _list) (list-head (cdr _list) (- k 1)))
			    (cons (car _list) nil)))))
(define list-tail (lambda (_list k)
		    (if (< k 0)
			error
			(if k
			    (list-tail (cdr _list) (- k 1))
			    _list))))
(define list-ref (lambda (_list k)
		    (if (< k 0)
		       error
		       (if k
		           (list-ref (cdr _list) (- k 1))
		           (car _list)))))
(define reverse-first-n (lambda (_list n)
		   (if (< n 0)
		       error
		       (if n
		         (if (= 1 n)
			     (cons (car _list)
				   nil)
			     (cons (list-ref _list (- n 1))
				   (reverse-first-n _list (- n 1))))
			 nil))))
(define reverse (lambda (_list)
		   (reverse-first-n _list (length _list))))

(define reduce-first-n (lambda (func _list n)
		   (if (< (length _list) (min n 2))
		       error
		       (if (= n 2)
		         (func (car _list) (car (cdr _list)))
			 (func (reduce-first-n func _list (- n 1)) (list-ref _list (- n 1)))))))

(define reduce (lambda (func _list)
		 (reduce-first-n func _list (length _list))))
(define reduce-with-initial (lambda (func _list ini)
			      (reduce func (cons ini _list))))

(define type-equal? (lambda (obj1 obj2)
		      (if (nullp obj1)
			  (nullp obj2)
			  (if (intp obj1)
			      (intp obj2)
			      (if (doublep obj1)
				  (doublep obj2)
				  (if (symbolp obj1)
				      (symbolp obj2)
				      (if (listp obj1)
					  (listp obj2)
					  (procedurep obj2))))))))
(define equal? (lambda (obj1 obj2)
		 (if (or (not (type-equal? obj1 obj2)) (procedurep obj1))
		     0
		     (if (nullp obj1)
			 1
			 (if (listp obj1)
			     (and (equal? (car obj1) (car obj2)) (equal? (cdr obj1) (cdr obj2)))
			     (= obj1 obj2))))))

(define assoc (lambda (obj alist)
		 (if (equal? obj (car (car alist)))
		     (car alist)
		     (if (nullp (cdr alist))
			 0
			 (assoc obj (cdr alist))))))
(define partition-true (lambda (proc alist)
		      (if (nullp alist) nil
		      (if (proc (car alist))
			  (if (nullp (cdr alist))
			      (cons (car alist) nil)
			      (cons (car alist)
				    (partition-true proc (cdr alist))))
			  (if (nullp (cdr alist))
			      nil
			      (partition-true proc (cdr alist)))))))
(define partition-false (lambda (proc alist)
		      (if (nullp alist) nil
		      (if (not (proc (car alist)))
			  (if (nullp (cdr alist))
			      (cons (car alist) nil)
			      (cons (car alist)
				    (partition-false proc (cdr alist))))
			  (if (nullp (cdr alist))
			      nil
			      (partition-false proc (cdr alist)))))))
(define list-partition (lambda (proc alist)
		    (if (nullp alist)
			(cons nil (cons nil nil))
		        (cons (partition-true proc alist) (cons (partition-false proc alist) nil)))))
(define list-sort (lambda (proc_ls alist_ls)
		      (if (>= 1 (length alist_ls))
			  alist_ls
			  (let ((result (list-partition
					 (lambda (x) (proc_ls x
							      (car alist_ls)))
					 (cdr alist_ls))))
			    (if (nullp (car result))
				(cons (car alist_ls)
				      (list-sort proc_ls (car (cdr result))))
			        (if (nullp (cdr result))
				    (append (list-sort proc_ls (car result))
					    (cons (car alist_ls) nil))
				    (append (list-sort proc_ls (car result))
					    (cons (car alist_ls)
						  (list-sort proc_ls (car (cdr result)))))))))))
		    