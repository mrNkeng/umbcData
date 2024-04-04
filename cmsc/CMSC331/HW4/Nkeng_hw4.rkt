#lang racket

#|
This code calculates the Grade Point Average (GPA) from
a list of student records, where each record contains the
course name, credit value, and grade. It filters out
invalid records and converts the raw grade to a GPA scale
before calculating the overall GPA. The result is rounded
to four decimal places.
|#


(require racket/trace)
(define record '(("Course" "Credits" "Grade")
                 ("CMSC 299" 2 "P")
                 ("CMSC 331" 3 87)
                 ("CMSC 341" 3 100)
                 ("CMSC 421" 3 85)
                 ("CHEM 201" 4 "Incomplete")
                 ("PHYS 201" 4 77)
                 ("CMSC 491" "error" 100)))

; converts a raw grade to a GPA value on a 4.0 scale.
(define (convert-to-gpa grade)
  (cond ((>= grade 90) 4.0)
        ((>= grade 80) 3.0)
        ((>= grade 70) 2.0)
        ((>= grade 60) 1.0)
        (else 0)))

#| receives a list of student records, filters out any invalid records,
calls functions to calculate the total grade credits and total credits.
The GPA is then calculated as total grade credits divided by total
credits. If the total credits are zero, the function returns 0.
The final GPA value is rounded to four.
|#
(define (calc student-records)
  (let* ((filtered-records (filter (lambda (x) (and (number? (cadr x)) (number? (caddr x)))) (cdr student-records)))
         (TGC (total-grade-credit filtered-records))
         (TC (total-credit filtered-records)))
    (if (zero? TC)
        0
        (round-decimal (/ TGC TC)))))

; This function takes a floating-point number and rounds it four decimal places.
(define (round-decimal num)
  (/ (round (* num 10000)) 10000.0))

;  a recursive function that calculates the total grade credits.
(define (total-grade-credit records)
  (cond
   ((null? records) 0)
   (else (+ (* (convert-to-gpa (caddr (car records))) (cadr (car records)))
            (total-grade-credit (cdr records))))))

; This is another recursive function that calculates the total credit value.
(define (total-credit records)
  (cond
   ((null? records) 0)
   (else (+ (cadr (car records)) (total-credit (cdr records))))))

; test call
(calc record)

