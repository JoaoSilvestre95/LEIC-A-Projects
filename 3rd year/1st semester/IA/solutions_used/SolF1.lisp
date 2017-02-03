;;; These functions, and any other ones needed must be implemented

;;; Utilizar estes includes para os testes na versao local
;;; comentar antes de submeter
;;(load "datastructures.lisp")
;;(load "auxfuncs.lisp")

;;; Utilizar estes includes para a versao a submeter
; tirar o comentario antes de submeter
(load "datastructures.fas")
(load "auxfuncs.fas")

(defun isObstaclep (pos track)
  "check if there is an obstacle at position pos of the track"
  (not (nth (second pos) (nth (first pos) (track-env track))))
)

(defun isGoalp (st)
  "check if st is a goal state"
  (let ((endPos (track-endpositions (state-track st))))
    (dolist (x endPos)
      do (if (equal x (state-pos st)) (return t))))
)

(defun nextState (st act) ;st-state ; act-(acx, acy)
  "generate the nextState after state st and action act"
  (let* ((cost 1) (vel (list (+ (first (state-vel st)) (first act)) (+ (second (state-vel st)) (second act))))
        (pos (list (+ (first (state-pos st)) (first vel)) (+ (second (state-pos st)) (second vel))))
        (newState (make-STATE :POS pos
        	      :VEL vel
        	      :ACTION act
        	      :COST cost
                :TRACK (state-track st)
        )))
  (cond
    ((isObstaclep pos (state-track st)) (progn (setf (state-cost newState) 20) (setf (state-vel newState) '(0 0)) (setf (state-pos newState) (state-pos st))))
    ((isGoalp newState) (setf (state-cost newState) -100))
  )
  newState
  ))
