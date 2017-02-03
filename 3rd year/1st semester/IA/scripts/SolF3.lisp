(load "datastructures.fas")
(load "auxfuncs.fas")


;;; TAI position
(defun make-pos (c l)
  (list c l))
(defun pos-l (pos)
  (first pos))
(defun pos-c (pos)
  (second pos))

;;; TAI acceleration
(defun make-acce (c l)
  (list c l))
(defun acce-l (pos)
  (first pos))
(defun acce-c (pos)
  (second pos))

;;; TAI velocity
(defun make-vel (c l)
  (list c l))
(defun vel-l (pos)
  (first pos))
(defun vel-c (pos)
  (second pos))


;; Solution of phase 1

(defun getTrackContent (pos track)
  (nth (pos-c pos) (nth (pos-l pos) (track-env track))))

(defun getTrackBfsContent (pos track)
  (nth (pos-c pos) (nth (pos-l pos) track))
)
;; Pedir 0,4
(defun isObstaclep (pos track)
  "check if the position pos is an obstacle"
  (or (< (pos-l pos) 0) (< (pos-c pos) 0)
      (>= (pos-l pos) (pos-l (track-size track)))
      (>= (pos-c pos) (pos-c (track-size track)))
      (null (getTrackContent pos track))))

;; Pedir 0,4
(defun isGoalp (st)
  "check if st is a solution of the problem"
  (let ((current-position (state-pos st))
	(track (state-track st)))
    (and (member current-position (track-endpositions track) :test #'equalp)
	 T)))

;; Pedir 1,2
(defun nextState (st act)
  "generate the nextState after state st and action act from prolem"
  (let ((new-state (make-state :action act :track (state-track st))))
    (setf (state-vel new-state)
	  (make-vel (+ (vel-l (state-vel st)) (acce-l act))
		    (+ (vel-c (state-vel st)) (acce-c act))))
    (setf (state-pos new-state)
	  (make-pos (+ (pos-l (state-pos st)) (vel-l (state-vel new-state)))
		    (+ (pos-c (state-pos st)) (vel-c (state-vel new-state)))))
    (setf (state-cost new-state)
	  (cond ((isGoalp new-state) -100)
		((isObstaclep (state-pos new-state) (state-track new-state)) 20)
		(T 1)))
    (when (= (state-cost new-state) 20)
      (setf (state-vel new-state) (make-vel 0 0))
      (setf (state-pos new-state) (make-pos (pos-l (state-pos st))
					    (pos-c (state-pos st)))))
    (values new-state)))

;; Solution of phase 2

;;; Pedir
(defun nextStates (st)
  "generate all possible next states"
  (let ((successors nil))
    (dolist (act (possible-actions) successors)
      (let ((new-state (nextState st act)))
	(if (not (member new-state successors :test #'equalp))
	    (push new-state successors))))))

;;; Solucao e uma seq ordenada de estados
(defun solution (node)
  (let ((seq-states nil))
    (loop
      (when (null node)
	(return))
      (push (node-state node) seq-states)
      (setf node (node-parent node)))
    (values seq-states)))


    ;;; limdepthfirstsearch
(defun limdepthfirstsearch (problem lim &key cutoff?)
  "limited depth first search
     st - initial state
     problem - problem information
     lim - depth limit"
  (labels ((limdepthfirstsearch-aux (node problem lim)
	     (if (isGoalp (node-state node))
		 (solution node)
		 (if (zerop lim)
		     :cutoff
		     (let ((cutoff? nil))
		       (dolist (new-state (nextStates (node-state node)))
			 (let* ((new-node (make-node :parent node :state new-state))
				(res (limdepthfirstsearch-aux new-node problem (1- lim))))
			   (if (eq res :cutoff)
			       (setf cutoff? :cutoff)
			       (if (not (null res))
				   (return-from limdepthfirstsearch-aux res)))))
		       (values cutoff?))))))
    (let ((res (limdepthfirstsearch-aux (make-node :parent nil :state (problem-initial-state problem))
					problem
					lim)))
      (if (eq res :cutoff)
	  (if cutoff?
	      :cutoff
	      nil)
	  res))))

;iterlimdepthfirstsearch
(defun iterlimdepthfirstsearch (problem &key (lim most-positive-fixnum))
  "limited depth first search
     st - initial state
     problem - problem information
     lim - limit of depth iterations"
  (let ((i 0))
    (loop
      (let ((res (limdepthfirstsearch problem i :cutoff? T)))
	(when (and res (not (eq res :cutoff)))
	  (return res))
	(incf i)
	(if (> i lim)
	    (return nil))))))

;; Solution of phase 3

(defun getLSize (track)
  (return-from getLSize (first (track-size track)))
)
(defun getCSize (track)
  (return-from getCSize (second (track-size track)))
)


(defun createBfsTrack (track)
  (let ((matrix '()))
    (loop for x from 0 to (- (getLsize track) 1) do
      (push (make-list (getCSize track) :initial-element most-positive-fixnum) matrix)
    )
    (return-from createBfsTrack matrix)
  )
)

(defun bfs (track);state: initial state; track: track problem
  (let* ((htrack (createBfsTrack track)) (stack '()))
        (dolist (endPositions (track-endpositions track))
          (setf (nth (pos-c endPositions) (nth (pos-l endPositions) htrack)) 0)
          (push (make-state :pos endPositions :vel (make-vel 0 0) :action nil :cost 0 :track track) stack)
        )
        (loop while (not (= (list-length stack) 0)) do
          (let ((newState (pop stack)))
            (setf (state-vel newState) (make-vel 0 0))
            (dolist (childState (nextStates newState))
              (if (not (isObstaclep (state-pos childState) (state-track childState)))
                (if  (= ( getTrackBfsContent (state-pos childState) htrack) most-positive-fixnum)
                  (progn
                    (setf stack (append stack (list childState)))
                    (setf (nth (pos-c (state-pos childState)) (nth (pos-l (state-pos childState)) htrack)) (+ 1 (getTrackBfsContent (state-pos newState) htrack)))
                  )
                )
              )
            )
          )
        )
        (return-from bfs htrack)
  )
)

(defun bfsH (st)
  (setf (state-other st) 0)
  (let ((open (list st)) (closed '()))
    (loop while open do
      (let* ((newStatei (pop open)) (newState (make-state :pos (state-pos newStatei) :vel (make-vel 0 0) :track (state-track newStatei) :other (state-other newStatei))))
        (push newState closed)
        (if (isGoalp newState) (return-from bfsH (state-other newState)))
          (dolist (childState (nextStates newState))
            (if (not(isObstaclep (state-pos childState) (state-track childState)))
              (if (and (not (member childState open :test #'comparePosition)) (not (member childState closed :test #'comparePosition)) )
                (progn
                  (setf (state-other childState) (+ (state-other newState) 1))
                  (setf open (append open (list childState)))
                )
              )
            )
          )
      )
    )
  )
)

;; Heuristic
(defun compute-heuristic (st)
  (bfsH st)
)

(defun makeNodeHeuristic (state parent)
  (let* ((h (compute-heuristic state)) ;distance from current node to goal
        (g (state-cost state)) ;distance from current node to starting node
        (f (+ h g)) ;distance from satrting node to goal using this node
        (node (make-node :parent parent :state state :h h :g g :f f)))
        (return-from makeNodeHeuristic node)
  )
)

(defun comparePosition (x y) ;Recevies states
  (return-from comparePosition (equal (state-pos x) (state-pos y)))
)

;;; A*
(defun a* (problem)
  (let* ((h (compute-heuristic (problem-initial-state problem)))
        (g 0)
        (nodeStart (make-node :state (problem-initial-state problem) :h h :g g :f (+ g h)))
        (openSet (list nodeStart)))
        (loop while (not (= (list-length openSet) 0)) do
          (let ((min most-positive-fixnum) (lowestNode (first openSet)))
            (dolist (x openSet)
              (if (< (node-f x) min)
                (progn (setf min (node-f x)) (setf lowestNode x)) ;defines the node with the lowest f
              )
            )
            (if (isGoalp (node-state lowestNode));Check if is the final node
              (return-from a* (solution lowestNode))
            )
            (setf openSet (remove lowestNode openSet)) ;delet the lowest node that is gonna be expand it
            (dolist (x (nextStates (node-state lowestNode)))
              (if (not (isObstaclep (state-pos x) (state-track x)))
                (let* ((h (compute-heuristic x))
                      (g (+ (state-cost x) (node-g lowestNode)))
                      (childrenNode (make-node :state x :parent lowestNode :g g :h h :f (+ h g))))
                  (push childrenNode openSet)
                )
              )
            )
          )
        )
        (return-from a* nil)
  )
)


(defun compute-best-heuristic (state heuristicTrack)
  (let* ((distFinal (getTrackBfsContent (state-pos state) heuristicTrack))
          (velX (abs (vel-c (state-vel state))))
          (velY (abs (vel-l (state-vel state))))
          (maxVel (max velX velY))
          (cost 0)
          (distance 0)
        )
    (loop while (< distance distFinal) do
      (setf maxVel (incf maxVel))
      (setf distance (+ distance maxVel))
      (setf cost (incf cost))
    )
    (return-from compute-best-heuristic cost)
  )
)

;;;Best-Search

(defun best-search (problem)
    (let* ((heuristicTrack (bfs (state-track (problem-initial-state problem))))
          (hStart (compute-best-heuristic (problem-initial-state problem) heuristicTrack))
          (gStart 0)
          (nodeStart (make-node :state (problem-initial-state problem) :h hStart :g gStart :f (+ gStart hStart)))
          (openSet (list nodeStart)))
          (loop while openSet do
             ;defines the node with the lowest f
            (let ((min most-positive-fixnum) (lowestNode (first openSet)))
              (dolist (x openSet)
                (if (< (node-f x) min)
                  (progn (setf min (node-f x)) (setf lowestNode x)) ;defines the node with the lowest f
                )
              )
              (if (isGoalp (node-state lowestNode));Check if is the final node
                (return-from best-search (solution lowestNode))
              )
              (setf openSet (remove lowestNode openSet))
              (dolist (x (nextStates (node-state lowestNode)))
                (if (not (isObstaclep (state-pos x) (state-track x)))
                  (let* ((h (compute-best-heuristic x heuristicTrack))
                        (g (+ (state-cost x) (node-g lowestNode)))
                        (childrenNode (make-node :state x :parent lowestNode :g g :h h :f (+ h g))))
                    (push childrenNode openSet)
                  )
                )
              )
            )
          )
          (return-from best-search nil)
    )
)
