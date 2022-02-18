!================================================================================
!   Additional routines added by Brendan McCormick 2018/11/09 to pass
!   results of nuc stat tensor calc (coulex routine) to C++.
!   Remember to call (in this order) setup_coulex, freader, coulparCM and
!   coulex before you pull these values.
!   The returned stat tensor ignores imaginary component (which is presumably 0).
!   and kidx and kqidx are reversed for rrho due to reversed array access in C++
!================================================================================
      subroutine getcoulex(lvl, rho_cre, xsect)
      
      complex RHOB,RHOC
      real*4 DSIG,DSIGLB,RU
      real*4 rho_cre(5,3)
      real*4 xsect
      integer k,kidx,kqidx,lvl
      COMMON/BL29/RHOB(25,3,5),RHOC(25,3,5)
      COMMON/BL46/DSIG(25),DSIGLB(25),RU(25)

      
      xsect=DSIG(lvl)
      do k=0,4,2
        do kq=0,k,1
          kidx=k/2+1
          kqidx=kq+1
          rho_cre(kqidx,kidx)=real(RHOC(lvl,kidx,kqidx))
        enddo
      enddo
      
      end
      
!=============================================================================
!	wdbsubs
!==============================================================================
      SUBROUTINE FREADER(readfile,inperr)
!
!     THIS ROUTINE READS AND CHECKS THE INPUT DATA
!
!	reads input from file specified in the input line
!	execute at least once before calling coulex routine


      LOGICAL ERR
      REAL INTM1
      REAL INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      INTEGER OURHOB,OURHOC,OURHOX
      REAL MEM
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL22/THETA
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL52/IPURG
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop
      DIMENSION FINPUT(72),A(72)
	COMMON/OPT/IOPT         !! A OUTPUT OPTION
	CHARACTER LINE*80
	character readfile*80
!
!     READ IN STARTS
!
	inperr=0
        open(unit=20,file=readfile,status='old',err=1500)

!      write(50,900)
 100  CONTINUE
      DO 101 NI=1,8
 101  FINPUT(NI)=0.0
      READ(20,901,END=105),(A(I), I=1,72)        !********
      CALL LEXEM(A,FINPUT,N,MODE,IERR)
      IF (N.LT.8 .AND. IERR.EQ.0) GOTO 102
      write(50,912) ! error message
      ERR = .TRUE.
 102  IF( FINPUT(1) .EQ. 0. ) GOTO 600
!     STATEMENT 600 MEANS  START EXECUTION OF THE JOB
      IF(FINPUT(1).LT.0.)GOTO 700
!     STATEMENT 700 MEANS  PURGE ALL PREVIOUS INPUT
!      write(50,902) (FINPUT(I), I=1,7)
      IF( FINPUT(1) .LE. 40. ) GOTO 110
!
!     PROGRAM STOPS HERE IF NO MORE DATA
 105  STOP
!
!     ASSIGN INPUT DATA TO PROPER VARIABLES
!
 110  IJUMP = IFIX( FINPUT(1) + .00001 )
      GOTO (501,502,503,504,505,506,507,508,509,510,511,512,513,514,
     1 515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,
     2 531,532,533,534,535,536,537,538,539,540),IJUMP
 501  CONTINUE
      NMAX = FINPUT(2)
      IF(NMAX.LT.2.OR.NMAX.GT.NDIM) CALL ERROR(1)
      GOTO 100
 502  CONTINUE
      NCM = FINPUT(2)
      IF(NCM.GE.1.AND.NCM.LE.NDIM)GOTO 100
      NCM = 2
      if(iop.eq.1)write(50,904)    ! writes comment NCM=2
      GOTO 100
 503  CONTINUE
      NTIME = FINPUT(2)
      IF(NTIME.LE.0) CALL ERROR(21)
      GOTO 100
 504  CONTINUE
      XIMAX = FINPUT(2)
      IF(XIMAX.LE.0..OR.XIMAX.GE.99.)CALL ERROR(2)
      GOTO 100
 505  CONTINUE
      EMMAX1 = FINPUT(2)
      IF(EMMAX1.LT.0.)CALL ERROR(3)
      GOTO 100
 506  CONTINUE
      ACCUR=FINPUT(2)
      IF(ACCUR.LE.0.)CALL ERROR(4)
      IF(ACCUR.LE.0.0001)GOTO 100
      ACCUR = 0.0001
      if(iop.eq.1)write(50,906) ! message: assumes accur = 0.0001
      GOTO 100
 507  CONTINUE
      OUXI = FINPUT(2)
      GOTO 100
 508  CONTINUE
      OUPSI = FINPUT(2)
      GOTO 100
 509  CONTINUE
      OUAMP = FINPUT(2)
      GOTO 100
 510  CONTINUE
      OUPROW = FINPUT(2)
      GOTO 100
 511  CONTINUE
      OURHOB = FINPUT(2)
      GOTO 100
 512  CONTINUE
      OURHOC = FINPUT(2)
      GOTO 100
 513  CONTINUE
      GOTO 100
 514  CONTINUE
      ALPHA = FINPUT(2)
      BETA = FINPUT(3)
      GAMMA = FINPUT(4)
      OURHOX = 1
      OURHOC = 1
      GOTO 100
 515  CONTINUE
      DIPOL = FINPUT(2)
      GOTO 100
 516  CONTINUE
      INTIN=FINPUT(2)
      IF(INTIN.GE.1)GOTO 100
      INTIN = 1
      if(iop.eq.1)write(50,908)     ! message
      GOTO 100
 517  CONTINUE
      IDN17 = 1
      ZP = FINPUT(2)
      A1 = FINPUT(3)
      IF(ZP.LE.0..OR.A1.LE.0.)CALL ERROR(5)
      IF(ZP.GT.A1)CALL ERROR(6)
      GOTO 100
 518  CONTINUE
      IDN18 = 1
      ZT = FINPUT(2)
      A2 = FINPUT(3)
      IF(ZT.LE.0..OR.A2.LE.0.)CALL ERROR(5)
      IF(ZT.GT.A2)CALL ERROR(6)
      GOTO 100
 519  CONTINUE
      IDN19 = 1
      EP = FINPUT(2)
      IF(EP.LE.0.)CALL ERROR(7)
      GOTO 100
 520  CONTINUE
      TLI = FINPUT(2)
      IF(TLI.LT.0..OR.TLI.GT.180.)CALL ERROR(8)
      TLBDG = TLI
      GOTO 100
 521  CONTINUE
      THI = FINPUT(2)
      IF(THI.LT.0..OR.THI.GT.180.)CALL ERROR(8)
      THETA = THI
      GOTO 100
 522  CONTINUE
      N = FINPUT(2)
      IF(N.LT.1.OR.N.GT.NDIM) CALL ERROR(9)
      SPIN(N) = FINPUT(3)
      EN(N) = FINPUT(4)
      IPAR(N) = FINPUT(5)
      BANDK(N)=FINPUT(6)
      IF(SPIN(N).LT.0.)CALL ERROR(10)
      IF(EN(N).LT.0.)CALL ERROR(11)
      IF(IPAR(N).EQ.0.0)IPAR(N)=1.0
      IF(IPAR(N).NE.1..AND.IPAR(N).NE.-1.)CALL ERROR(12)
      GOTO 100
 523  CONTINUE
      N = FINPUT(2)
      M = FINPUT(3)
      LAM=FINPUT(5)
      IF(LAM.EQ.0) LAM=2
      IF(N.LT.1.OR.N.GT.NDIM)CALL ERROR(9)
      IF(M.LT.1.OR.M.GT.NDIM)CALL ERROR(9)
      IF(LAM.LT.1.OR.LAM.GT.6)CALL ERROR(13)
      MEM(N,M,LAM)=FINPUT(4)
      IF(LAM.EQ.LAMDA(1).OR.LAM.EQ.LAMDA(2).OR.LAM.EQ.LAMDA(3).OR.LAM.EQ
     1.LAMDA(4).OR.LAM.EQ.LAMDA(5).OR.LAM.EQ.LAMDA(6).OR.LAM.EQ.LAMDA(7)
     2.OR.LAM.EQ.LAMDA(8).OR.LAM.EQ.LAMDA(9).OR.LAM.EQ.LAMDA(10).OR.
     3LAM.EQ.LAMDA(11).OR.LAM.EQ.LAMDA(12))GOTO 100
      LAMMAX = LAMMAX + 1
      LAMDA(LAMMAX) = LAM
      GOTO 100
 524  CONTINUE
      MAGEXC = 1
      N = FINPUT(2)
      M = FINPUT(3)
      LA= FINPUT(5)
      IF(LA.EQ.0) LA = 1
      LAM = LA + 6
      IF(N.LT.1.OR.N.GT.NDIM) CALL ERROR(9)
      IF(M.LT.1.OR.M.GT.NDIM) CALL ERROR(9)
      IF(LA.LT.1.OR.LA.GT.6) CALL ERROR(13)
      MEM(N,M,LAM)=FINPUT(4)
      IF(LAM.EQ.LAMDA(1).OR.LAM.EQ.LAMDA(2).OR.LAM.EQ.LAMDA(3).OR.LAM.EQ
     1.LAMDA(4).OR.LAM.EQ.LAMDA(5).OR.LAM.EQ.LAMDA(6).OR.LAM.EQ.LAMDA(7)
     2.OR.LAM.EQ.LAMDA(8).OR.LAM.EQ.LAMDA(9).OR.LAM.EQ.LAMDA(10).OR.
     3LAM.EQ.LAMDA(11).OR.LAM.EQ.LAMDA(12))GOTO 100
      LAMMAX = LAMMAX + 1
      LAMDA(LAMMAX) = LAM
      GOTO 100
 525  CONTINUE
      IDN25 = 1
      DTHETA = FINPUT(2)
	IOPT=0
	IF(DTHETA.LT.0.)IOPT=1
	DTHETA=ABS(DTHETA)
      IF(DTHETA.LE.0..OR.DTHETA.GE.180.)CALL ERROR(22)
      GOTO 100
 526  CONTINUE
      NGMAX = FINPUT(2)
      IF(NGMAX.LT.1.OR.NGMAX.GT.10)CALL ERROR(14)
      GOTO 100
 527  CONTINUE
      I = FINPUT(2)
      IF(I.LT.1.OR.I.GT.10)CALL ERROR(15)
      NSTART(I) = FINPUT(3)
      NSTOP(I) = FINPUT(4)
      EMMAX(I) = FINPUT(5)
      IF(NSTART(I).LT.1.OR.NSTART(I).GT.NDIM)CALL ERROR(16)
      IF(NSTOP(I).LT.1.OR.NSTOP(I).GT.NDIM)CALL ERROR(16)
      IF(NSTOP(I).LT.NSTART(I))CALL ERROR(17)
      IF(EMMAX(I).LT.0.)CALL ERROR(18)
      IF(NSTOP(I)-NSTART(I).GT.10) CALL ERROR(20)
      GOTO 100
 528  CONTINUE
      I1 = FINPUT(2)
      I2 = FINPUT(3)
      IF(I1.LT.1.OR.I1.GT.10)CALL ERROR(15)
      IF(I2.LT.1.OR.I2.GT.10)CALL ERROR(15)
      MASTER(I1,I2) = FINPUT(4)
      GOTO 100
 529  CONTINUE
      I = FINPUT(2)
      IF(I.LT.1.OR.I.GT.10)CALL ERROR(15)
      IEXCIT(I) = FINPUT(3)
      IF(IEXCIT(I).NE.1.AND.IEXCIT(I).NE.2)CALL ERROR(19)
      GOTO 100
 530  CONTINUE
      INTM1 = FINPUT(2)
      INTE1 = FINPUT(3)
      INTE2 = FINPUT(4)
      INTE3 = FINPUT(5)
      INTE4 = FINPUT(6)
      INTE5 = FINPUT(7)
      INTE6=FINPUT(8)
      CALL MATROT
      GOTO 100
 531  CONTINUE
 532  CONTINUE
 533  CONTINUE
 534  CONTINUE
 535  CONTINUE
 536  CONTINUE
 537  CONTINUE
 538  CONTINUE
 539  CONTINUE
 540  CONTINUE
      GOTO 100
!
!     START EXECUTION OF THE JOB
 600  IF(ERR)GOTO 710
      CALL CHECK
      IF(ERR)GOTO 710
      CALL START
      IF(ERR)GOTO 710
      RETURN
!
!     RETURN TO MAIN PROGRAM AND PURGE ALL PREVIOUS INPUT
 700  IPURG = 1
      RETURN
!
!     PRINT MESSAGE "EXECUTION TERMINATED"
 710  write(50,910)
      RETURN
!
 900  FORMAT( //, 32H1LIST OF NEW CARDS FOR THIS RUN. )
 901  FORMAT(72A1)
 902  FORMAT( 8F10.5 )
 904  FORMAT(24H PROGRAM ASSUMES NCM = 2)
 906  FORMAT(32HPROGRAM ASSUMES  ACCUR = 0.0001,/)
 908  FORMAT(28H PROGRAM ASSUMES  INTERV = 1)
 910  FORMAT(21H0EXECUTION TERMINATED)
 912  FORMAT(50H INPUT ERROR -- DATA CARD MUST CONTAIN LESS THAN 8
     141H NUMBERS AND LESS THAN 72 DATA CHARACTERS)
1500  write(6,*)' Input file error'
	inperr=1
	RETURN
      END
!=============================================================================
	subroutine coulpar(Eb,TSLBDG)
!
!	Changes beam energy and lab scattering angle parameters only
!


      INTEGER OURHOB,OURHOC,OURHOX
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      LOGICAL ERR
      REAL MEM,MULT
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON /BL8/ASQRT,B(200),IEX(200)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL11/INTEND
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL52/IPURG
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop

	Ep=Eb
	TLBDG=TSLBDG
	TLI=TSLBDG


!
!     PRINT-OUT OF NEW INPUT DATA
      if(iop.eq.1)write(50,900)
      if(iop.eq.1)write(50,902) ZP,A1,EP

      if(iop.eq.1)write(50,908) TLBDG
! 250  if(iop.eq.1)write(50,910) ZT,A2

!
 900  FORMAT(12H1COULEX 1978,/28H MULTIPLE COULOMB EXCITATION,
     18H PROGRAM,2X,26HFOR  E1 - E6  AND  M1 - M6//)
 902  FORMAT(32H0PROJECTILE CHARGE NUMBER  ZP = F6.2,14H,  MASS  A1 =  
     1F8.3,23HAMU,  LAB ENERGY  EP = F8.3,3HMEV)
 908  FORMAT(48H0SCATTERING ANGLE IN LABORATORY SYSTEM  TLBDG = F7.2,
     1 8H DEGREES)

	return
	end
!=============================================================================
!=============================================================================
	subroutine coulparCM(Eb,TCMDEG)
!
!	Changes beam energy and cm scattering angle parameters only
!


      INTEGER OURHOB,OURHOC,OURHOX
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      LOGICAL ERR
      REAL MEM,MULT
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON /BL8/ASQRT,B(200),IEX(200)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL11/INTEND
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL22/THETA
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL52/IPURG
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop

	Ep=Eb
	THETA=TCMDEG
	THI=TCMDEG

!
!     PRINT-OUT OF NEW INPUT DATA
      if(iop.eq.1)write(50,900)
      if(iop.eq.1)write(50,902) ZP,A1,EP

      if(iop.eq.1)write(50,906) THETA

!
 900  FORMAT(12H1COULEX 1978,/28H MULTIPLE COULOMB EXCITATION,
     18H PROGRAM,2X,26HFOR  E1 - E6  AND  M1 - M6//)
 902  FORMAT(32H0PROJECTILE CHARGE NUMBER  ZP = F6.2,14H,  MASS  A1 =  
     1F8.3,23HAMU,  LAB ENERGY  EP = F8.3,3HMEV)
 906  FORMAT(52H0SCATTERING ANGLE IN CENTER OF MASS SYSTEM  THETA = F7.2
     1,8H DEGREES)


	return
	end
!=============================================================================
	subroutine setup_coulex
!
!	this routine sets up the default parameters 
!	and prepares the factorial array etc
!
!
!	call it once in the main routine before calling the coulex routine
!

!     MULTIPLE COULOMB EXCITATION PROGRAM  COULEX 1980
!         DIMENSION OF THE ZETA ARRAY (NUMBER OF COUPLINGS) = 1200
!         DIMENSION OF THE CATALOGUE(NUMBER OF MAGN.SUBSTATES)=600
!         DIMENSION OF THE LEVEL SCHEME(NUMBER OF EXCITED STATES)=25
!
!     FOR INFORMATION WRITE TO:
!
!       J. DE BOER
!       AM COULOMBWALL 1
!       D-8046 GARCHING
!       WEST GERMANY
!
! *********************************************************************
! *                                                                   *
! *  THE INPUT MAY BE GIVEN AS INTEGERS OR DECIMAL NUMBERS            *
! *  WITH OR WITHOUT AN EXPONENT INDICATED BY AN E.                   *
! *  THE NUMBERS MAY BEGIN WITH A SIGN AND THEY MUST BE SEPARATED     *
! *  BY ONE COMMA OR ONE BLANK.                                       *
! *  AFTER THE NUMBERS THE CARD MAY BE FILLED WITH COMMENTS.          *
! *                                                                   *
! *  CONTENT OF THE DATA CARDS (DEFAULT VALUES IN PARENTHESIS)        *
! *                                                                   *
! *   1    NMAX (2)                                                   *
! *   2    NCM (2)                                                    *
! *   3    NTIME (3600)                                               *
! *   4    XIMAX (6.0)                                                *
! *   5    EMMAX1 (50.0)                                              *
! *   6    ACCUR (0.0001)                                             *
! *   7    OUXI (1)                                                   *
! *   8    OUPSI (1)                                                  *
! *   9    OUAMP (0)                                                  *
! *  10    OUPROW (0)                                                 *
! *  11    OURHOB (0)                                                 *
! *  12    OURHOC (0)                                                 *
! *  14    ALPHA(0)BETA(0)    GAMMA(0)                                *
! *  15    DIPOL (0.005)                                              *
! *  16    INTERV (10)                                                *
! *  17    ZP      A1                                                 *
! *  18    ZT      A2                                                 *
! *  19    EP                                                         *
! *  20    TLBDG (0.0)                                                *
! *  21    THETA (0.0)                                                *
! *  22    N       SPIN(N)    EN(N)           IPAR(N)(+1) BANDK(N)    *
! *  23    N       M          ME(N,M,LA)(0.0) LA (2)                  *
! *  24    N       M          MM(N,M,LA)(0.0) LA (1)                  *
! *  25    DTHETA (10.0)                                              *
! *  26    NGMAX (1)                                                  *
! *  27    I     NSTART(I)(0) NSTOP(I)(0)    EMMAX(I) (50.0)          *
! *  28    I1      I2         MASTER(I1,I2) (1)                       *
! *  29    I       IEXCIT(I) (2)                                      *
! *  30    INTM1(0)INTE1(0)   INTE2 (1.0)    INTE3(0)                 *
! *  31-40 FREE TO BE ASSIGNED                                        *
! *                                                                   *
! *********************************************************************
!
!
!
!
      INTEGER OURHOB,OURHOC,OURHOX
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      LOGICAL ERR
      REAL MEM,MULT
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON /BL8/ASQRT,B(200),IEX(200)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL11/INTEND
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL52/IPURG
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop
	data iop/0/ ! minimize output on repeated calls
!
!     THE FOLLOWING THREE QUANTITIES MUST BE ADJUSTED IF THE DIMENSIONS
!     IN THE PROGRAM ARE CHANGED
      NZMAX =  1200
      ICATMX = 600
      NDIM = 25
!
!     INITIALIZE FACTORIAL ARRAYS  B  AND  IEX
      A =  85.0
      ASQRT = SQRT(A)
      F = 1.0
      B(1) = 1.
      IEX(1) = 0
      DO 80 I=1,199
      F = F * FLOAT(I)/A
      IEX(I+1) = ALOG10(F)
      B(I+1) = F * 10.0**(-IEX(I+1))
!	write(20,*)I,IEX(I),B(I)
  80  CONTINUE
!
!     DEFAULT VALUES
 100  NMAX = 2
      NGMAX = 1
      NCM = 2
      NTIME = 3600
      INTERV = 10
      INTIN = INTERV
      XIMAX = 6.
      EMMAX1 = 50.0
      ACCUR = .0001
      DIPOL = 0.005
      OUXI = 1
      OUPSI = 1
      OUAMP = 0
      OUPROW = 0
      OURHOB = 0
      OURHOC = 0
      OURHOX = 0
      DTHETA = 10.
      TLI=0.0
      THI=0.0
      MAGEXC = 0
      DO 140 I=1,10
      EMMAX(I) = 50.0
      IEXCIT(I) = 2
      NSTART(I) = 0
      NSTOP(I) = 0
      DO 120 J=1,10
      MASTER(I,J) = 1
 120  CONTINUE
 140  CONTINUE
      LAMMAX = 0
      DO 160 LAM = 1,12
 160  LAMDA(LAM) = 1000
      DO 220 I=1,NDIM
      EN(I) = 0.0
      SPIN(I) = 0.0
      IPAR(I) = 1
      DO 200 J=1,NDIM
      DO 180 LAM=1,12
      MEM(I,J,LAM)=0.0
      MULT(I,J,LAM)=1.0
 180  CONTINUE
 200  CONTINUE
 220  CONTINUE
      ZP=0.0
      ZT=0.0
      A1=0.0
      A2=0.0
      EP=0.0
      INTE2 = 1.0
      INTM1=0.0
      INTE1=0.0
      INTE3=0.0
      ALPHA = 0.
      BETA = 0.
      GAMMA = 0.
      IDN17 = 0
      IDN18 = 0
      IDN19 = 0
      IDN25 = 0

	ERR = .FALSE.
      IPURG = 0
      INTEND = 0

	return
	end
!==============================================================================
	subroutine coulex
!
!
!
      INTEGER OURHOB,OURHOC,OURHOX
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      LOGICAL ERR
      REAL MEM,MULT
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON /BL8/ASQRT,B(200),IEX(200)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL11/INTEND
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL52/IPURG
      COMMON/BL55/DTHETA,DTLBDG
!
!     EXECUTION OF PROGRAM STARTS HERE
!
! 250  ERR = .FALSE.
!      CALL ZCLOCK(TIME01)
!      CALL READER
!      IF(IPURG.EQ.1)GOTO 100
!      IF(ERR) GOTO 250



!      ASSIGN 600 TO ITT
!      IF(NANGLE.GT.1) ASSIGN 500 TO ITT
      CALL PREP1
      IF(ERR) GOTO 250
!      CALL ZCLOCK(TIME02)
!      TPREP = TIME02 - TIME01
!      write(50,908) TPREP
! 300  CALL ZCLOCK(TIME1)
300	continue
      CALL PREP2
      IF(ERR) GOTO 250
!      CALL ZCLOCK(T1)
      CALL INTG
      IF(ERR) GOTO 250
!      CALL ZCLOCK(T2)
!      TINTG = T2 - T1
!      write(50,904) TINTG
      IF(OURHOB.EQ.0.AND.OURHOC.EQ.0.AND.OURHOX.EQ.0)
     1GOTO 420
      CALL TENS1
      IF(ERR) GOTO 250
!      CALL ZCLOCK(T3)
!      TTENS = T3 - T2
 420  CALL SIGM
      IF(ERR) GOTO 250
!      CALL ZCLOCK(TIME2)
!      IF(OURHOB.NE.0.OR.OURHOC.NE.0.OR.OURHOX.NE.0)
!     1write(50,906) TTENS
      IF(NANGLE.GT.1) GOTO 500
      GOTO 600
!      GOTO ITT, (600,500)
!
!     ESTIMATION OF TOTAL INTEGRATION TIME AFTER FIRST ANGLE
! 500  ESTTIM = (TIME2-TIME1)*FLOAT(NANGLE)

500	continue
!      write(50,900) ESTTIM

!      ASSIGN 600 TO ITT
!      IF(ESTTIM.LT.FLOAT(NTIME))GOTO 600
!      write(50,902)
!      GOTO 250

 600  IF(INTEND.EQ.1) GOTO 250
      IF(SIMP.NE.0.0) GOTO 300
      GOTO 250


250   RETURN

!
 900  FORMAT(21H0ESTIMATED JOB TIME = F10.3,4H SEC)
 902  FORMAT(44H0EXCEEDS ALLOWED TIME - EXECUTION TERMINATED)
 904  FORMAT(23H0TIME FOR INTEGRATION =F10.3,4H SEC//)
 906  FORMAT(44H0TIME FOR CALCULATING STATISTICAL TENSORS = F10.3,
     14H SEC)
 908  FORMAT(24H0TIME FOR PREPARATION = F10.3,4H SEC)
      END

!============================================================================
      SUBROUTINE AMPDER(AMP,AMPDOT,K)
!
!     THIS ROUTINE DETERMINES THE VALUE IR, FOR WHICH AMPDOT(IR,L) IS
!     CALCULATED
!
      COMPLEX AMP,AMPDOT
      INTEGER SSTART,SSTOP
      DIMENSION AMP(600,4),AMPDOT(600,4)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL5/NZ
      COMMON/BL12/LMX,IR1,IR2,N1,N2
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL40/SSTART(31),SSTOP(30)
!
      IF(K.EQ.2)GOTO 100
!     SETS INDEX COUNTER FOR ZETA-ARRAY EQUAL 0
      NZ = 0
 100  IF(SPIN(N1).EQ.0.)GOTO 300
!
!     IR - LOOP FOR GROUND STATE SPIN .NE. 0
      DO 200 IR=IR1,IR2
      N = CAT(IR,1)
      CALL LAISUM(AMP,AMPDOT,IR,N,LMX)
 200  CONTINUE
      RETURN
!
!     IR - LOOP FOR GROUND STATE SPIN = 0
 300  DO 500 N=N1,N2
      IR = SSTART(N) - 1
 400  IR = IR + 1
      CALL LAISUM(AMP,AMPDOT,IR,N,LMX)
      IF(CAT(IR,3).LT.-0.1)GOTO 400
 500  CONTINUE
      RETURN
      END
      SUBROUTINE CHECK
!
!     THIS ROUTINE CHECKS THE INPUT DATA
!
      LOGICAL ERR
      INTEGER OURHOB,OURHOC,OURHOX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL19/ERR
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
!
!     CHECK IF PROJECTILE GROUPS AND TARGET GROUPS ARE SEPARATED
!     THIS PART ALSO DETERMINES THE VARIABLES  IEXNUM  AND  IP
      J = IEXCIT(1)
      IEXNUM = 1
      IP = 1
      DO 100 I=1,NGMAX
      IF(IEXCIT(I).EQ.J)GOTO 100
      IP = I
      IEXNUM = IEXNUM + 1
      J = IEXCIT(I)
 100  CONTINUE
      IF(IEXNUM.LE.2)GOTO 120
      ERR = .TRUE.
      write(50,900) ! error message
      RETURN
!
!     CHECK OF GROUND STATE SPIN, GROUND STATE ENERGY AND EMMAX
 120  DO 140 K=1,IEXNUM
      J = 1
      IF(K.EQ.2) J=NSTART(IP)
      IF(SPIN(J).LE.3.5)GOTO 125
      ERR = .TRUE.
      write(50,902) J,SPIN(J) ! error message
 125  IF(EN(J).EQ.0.)GOTO 130
      ERR = .TRUE.
      write(50,904) J,EN(J) ! error message
 130  DO 139 I=1,NGMAX
      NGRD = 1
      IF(IEXNUM.EQ.2.AND.I.GE.IP) NGRD=NSTART(IP)
      IF(EMMAX(I).GE.SPIN(NGRD))GOTO 139
      ERR = .TRUE.
      write(50,906) I,EMMAX(I) ! error message
 139  CONTINUE
 140  CONTINUE
!
!     CHECK OF NSTART- AND NSTOP-ARRAY
      IF(NGMAX.EQ.1)GOTO 165
      DO 160 I=2,NGMAX
      J = I-1
      IF(NSTART(I)-NSTOP(J).EQ.1)GOTO 160
      ERR = .TRUE.
      write(50,908) J,NSTOP(J),I,NSTART(I) ! error message
 160  CONTINUE
!
!     CHECK OF NCM AND NMAX
 165  IF(NGMAX.LE.NMAX)GOTO 170
      ERR = .TRUE.
      write(50,910) NMAX,NGMAX  ! error message
 170  IF(NCM.LE.NMAX)GOTO 180
      write(50,912) NMAX,NCM
      NCM = 2
!
!     CHECK IF INPUT DATA CONTAIN EP,ZP,A1,ZT,A2
 180  IF(IDN17.EQ.1.AND.IDN18.EQ.1.AND.IDN19.EQ.1)GOTO 190
      ERR = .TRUE.
      write(50,914)  ! error message
!
!     CHECK IF ALL SPINS ARE EITHER INTEGER OR HALF INTEGER
 190  DO 220 K=1,IEXNUM
      N1 = 1
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IF(K.EQ.1)GOTO 195
      N1 = NSTART(IP)
      N2 = NMAX
 195  DO 210 N=N1,N2
      S = SPIN(N)-SPIN(N1)
      J = S
      DIFF = S - FLOAT(J)
      IF(DIFF.LT.0.01)GOTO 210
      ERR = .TRUE.
      write(50,916) N1,SPIN(N1),N,SPIN(N)
 210  CONTINUE
 220  CONTINUE
      RETURN
!
 900  FORMAT(64H0ERROR  -  TARGET GROUPS AND PROJECTILE GROUPS ARE NOT S
     1EPARATED//21H0EXECUTION TERMINATED)
 902  FORMAT(6H0SPIN(I2,4H) = F4.1/
     147H0ERROR  -  GROUND STATE SPIN MUST BE  .LT.  3.5)
 904  FORMAT(4H0EN(I2,4H) = F8.4,4H MEV/
     149H0ERROR  -  GROUND STATE ENERGY MUST BE  .EQ.  0.0)
 906  FORMAT(7H0EMMAX(I2,4H) = F4.1/
     149H0ERROR  -  EMMAX MUST BE  .GE.  GROUND STATE SPIN)
 908  FORMAT(7H0NSTOP(I2,4H) = I2,3X,7HNSTART(I2,4H) = I2/
     151H0ERROR  -  NSTART(I+1) - NSTOP(I)  MUST BE  .EQ.  1)
 910  FORMAT(8H0NMAX = I2,4X8HNGMAX = I2/
     136H0ERROR  -  NGMAX MUST BE  .LE.  NMAX)
 912  FORMAT(8H0NMAX = I2,4X,6HNCM = I2/25H0PROGRAM ASSUMES  NCM = 2)
 914  FORMAT('   ERROR  -  SOME OF THE FOLLOWING INPUT QUANTITIES ARE
     1 MISSING  EP, ZP, A1, ZT, A2 ')
 916  FORMAT(6H0SPIN(I2,4H) = F4.1,4X,5HSPIN(I2,4H) = F4.1/9H0ERROR  -
     159H  FOR EACH NUCLEUS ALL SPINS MUST BE EITHER INTEGER OR HALF
     28H INTEGER)
      END
      SUBROUTINE CMLAB(A1,A2,EP,EN,NMAX,TLBDG,TCMDG,ZLBDG,R3,R4,EPP,ETP)
!
!     THIS ROUTINE TRANSFORMS FROM LAB-SYSTEM TO CM-SYSTEM
!     THE FORMULAS ARE FROM ALDER/WINTHER, "ELECTROMAGNETIC EXCITATION"
!     NOTH-HOLLAND PUBL.CO., AMSTERDAM (1975), P. 263 - 268
!
      LOGICAL ERR
      DIMENSION EN(25),R3(25),R4(25),EPP(25),ETP(25)
      DIMENSION TCMDG(25),TCMRAD(25),ZLBDG(25),ZLBRAD(25)
      COMMON/BL19/ERR
!
      TLBRAD = TLBDG/57.2957795
      ARED = 1.0 + A1/A2
      EMAX = EP/ARED
      DO 200 N=1,NMAX
      IF (EN(N).LT.EMAX) GOTO 100
!     STOPS CALCULATION IF EXCITATION ENERGY IS KINEMATICALLY FORBIDDEN
      write(50,900) EMAX ! error message
      GOTO 850
 100  EPMIN = EP - EN(N)*ARED
      TAUP = SQRT(EP/EPMIN)
      TAU = TAUP * A1/A2
      IF (TAU.LE.1.0) GOTO 120
      TMXDG = ASIN(1.0/TAU) * 57.2957795
      IF (TMXDG.GE.TLBDG) GOTO 120
!     STOPS CALCULATION IF LABORATORY SCATTERING ANGLE IS KINEMATICALLY
!     FORBIDDEN
      write(50,902) TMXDG  ! error message
      GOTO 850
!
!     COMPUTATION OF CM SCATTERING ANGLE TCMDG(N)
 120  TCMRAD(N) = TLBRAD + ASIN(TAU*SIN(TLBRAD))
      TCMDG(N) = TCMRAD(N)*57.2957795
      IF (TAU.LE.1.0) GOTO 140
      write(50,904) TCMDG(N),N   ! information
!     TCMDG(N) = 180.+2.*TLBDG-TCMDG(N)
      TCMRAD(N) = TCMDG(N)/57.2957795
!
!     COMPUTATION OF LAB RECOIL ANGLE ZLBDG(N)
 140  ZCMDG = 180.0 - TCMDG(N)
      ZCMRAD = ZCMDG/57.2957795
      ZLBRAD(N) = ATAN(SIN(ZCMRAD)/(COS(ZCMRAD)+TAUP))
      ZLBDG(N) = ZLBRAD(N)*57.2957795
      IF(ABS(TCMDG(N)-180.).LT.1.E-10)GOTO 160
!
!     COMPUTATIION OF SOLID ANGLE RATIOS  R3(N)  AND  R4(N)
      R3(N)=(SIN(TLBRAD)/SIN(TCMRAD(N)))**2*ABS(COS(TCMRAD(N)-TLBRAD))
      R4(N)=(SIN(ZLBRAD(N))/SIN(ZCMRAD))**2*ABS(COS(ZCMRAD-ZLBRAD(N)))
      GOTO 180
 160  R3(N) = 1.0/(1.0-TAU)**2
      R4(N) = 1.0/(1.0+TAUP)**2
 180  R3(N) = 1.0/R3(N)
      R4(N) = 1.0/R4(N)
!
!     COMPUTATION OF LAB ENERGIES OF SCATTERED PARTICLES
      EPP(N)=(A2/(A1+A2))**2*(1.0+TAU*TAU+2*TAU*COS(TCMRAD(N)))*EPMIN
      ETP(N)=A1*A2/(A1+A2)**2*(1.+TAUP*TAUP+2.*TAUP*COS(ZCMRAD))*EPMIN
 200  CONTINUE
      RETURN
!
!     ERROR EXIT
!
 850  ERR = .TRUE.
      RETURN
!
 900  FORMAT(45H0ERROR- MAXIMUM ALLOWED EXCITATION ENERGY IS F8.4,
     14H MEV)
 902  FORMAT(44H0ERROR- MAXIMUM ALLOWED SCATTERING ANGLE IS F7.2,
     18H DEGREES)
 904  FORMAT(39H0SECOND POSSIBLE CM SCATTERING ANGLE IS F7.2,
     117H DEGREES FOR N = I3)
      END
      FUNCTION DJMM(BETA,RJ,RM,RMP)
!
!     THIS ROUTINE COMPUTES THE D-FUNCTION ACCORDING TO EQ. (I.4.6)
!
      COMMON /BL8/ASQRT,B(200),IEX(200)
!
      J=2.001*RJ
      M=2.001*RM
      MP=2.001*RMP
!	write(35,*)' '
!	write(35,*)' J,M,MP,beta = ',J,M,MP,beta
      IF(J.LT.IABS(M).OR.J.LT.IABS(MP).OR.J.LT.0) GOTO 200
      BE=BETA/57.295779
      CB=COS(BE/2.0)
      SB=SIN(BE/2.0)
!	write(35,*)' BE,CB,SB = ',BE,CB,SB
      JA=(J+MP)/2+1
      JB=(J-MP)/2+1
      JC=(J+M)/2+1
      JD=(J-M)/2+1
!	write(35,*)' JA,JB,JC,JD= ',JA,JB,JC,JD
      B1 = B(JA)*B(JB)*B(JC)*B(JD)
      IEX1 = IEX(JA)+IEX(JB)+IEX(JC)+IEX(JD)
!	write(35,*)' B1,IEX1 = ',B1,IEX1
      MINSIG=0
      IF(M+MP.LT.0) MINSIG=-M-MP
      MAXSIG=J-M
      IF(M.LT.MP) MAXSIG=J-MP
      ISIG=MINSIG
!	write(35,*)' minsig,maxsig = ',minsig,maxsig
      DJMM = 0.0
!
!     SUMMATION OVER SIGMA
 100  JA=ISIG/2+1
      JB=(J-M-ISIG)/2+1
      JC=(J-MP-ISIG)/2+1
      JD=(M+MP+ISIG)/2+1
!	write(35,*)' ISIG,JA,JB,JC,JD= ',ISIG,JA,JB,JC,JD
      FASE=(-1.0)**((J-MP-ISIG)/2)
      IC=ISIG+(M+MP)/2
      IS=J-ISIG-(M+MP)/2
!	write(35,*)' FASE,IC,IS =',FASE,IC,IS
      B2 = B(JA)*B(JB)*B(JC)*B(JD)
      IEX2 = IEX(JA)+IEX(JB)+IEX(JC)+IEX(JD)
!	write(35,*)' B2,IEX2 = ',B2,IEX2
      DJMM=DJMM+FASE*CB**IC*SB**IS*SQRT(B1/(B2*B2)*10.0**(IEX1-2*IEX2))
!	write(35,*)' ISIG,DJMM = ',ISIG,DJMM
      ISIG=ISIG+2
      IF(ISIG.LE.MAXSIG) GOTO 100
      RETURN
!
!     EXIT IF ERROR IN DJMM - ARGUMENTS
!
 200  write(50,900) ! error message
      STOP
!
 900  FORMAT(25H0 ERROR IN DJMM-ARGUMENTS)
      END
      SUBROUTINE ERROR(I)
!
!     THIS ROUTINE PRINTS ERROR MESSAGES AND SETS LOGICAL VARIABLE
!     ERR TO .TRUE.
!
      LOGICAL ERR
      COMMON/BL19/ERR
      COMMON/BL32/NMAX,NDIM
!
      ERR = .TRUE.
!
!     PRINTS ERROR MESSAGE ACCORDING TO VALUE OF I
!
      GOTO(101,102,103,104,105,106,107,108,109,110,111,112,113,114,
     1 115,116,117,118,119,120,121,122),I
 101  write(50,901) NDIM
      RETURN
 102  write(50,902)
      RETURN
 103  write(50,903)
      RETURN
 104  write(50,904)
      RETURN
 105  write(50,905)
      RETURN
 106  write(50,906)
      RETURN
 107  write(50,907)
      RETURN
 108  write(50,908)
      RETURN
 109  write(50,909) NDIM
      RETURN
 110  write(50,910)
      RETURN
 111  write(50,911)
      RETURN
 112  write(50,912)
      RETURN
 113  write(50,913)
      RETURN
 114  write(50,914)
      RETURN
 115  write(50,915)
      RETURN
 116  write(50,916) NDIM
      RETURN
 117  write(50,917)
      RETURN
 118  write(50,918)
      RETURN
 119  write(50,919)
      RETURN
 120  write(50,920)
      RETURN
 121  write(50,921)
      RETURN
 122  write(50,922)
      RETURN
!
 901  FORMAT(46H INPUT ERROR  --  NMAX MUST BE .GE. 2 AND .LE.,I2/)
 902  FORMAT(54H INPUT ERROR  --  XIMAX MUST BE .GT. 0.0 AND .LT. 99.0/)
 903  FORMAT(41H INPUT ERROR  --  EMMAX1 MUST BE .GE. 0.0/)
 904  FORMAT(40H INPUT ERROR  --  ACCUR MUST BE .GT. 0.0/)
 905  FORMAT(53H INPUT ERROR  --  CHARGE NUMBER AND MASS NUMBER MUST  
     19HBE .GT. 0/)
 906  FORMAT(53H INPUT ERROR  --  CHARGE NUMBER MUST BE .LE. MASS NUM
     13HBER/)
 907  FORMAT(53H INPUT ERROR  --  ENERGY OF PROJECTILE MUST BE .GT. 0/)
 908  FORMAT(53H INPUT ERROR  --  SCATTERING ANGLE MUST BE BETWEEN 0  
     115HAND 180 DEGREES/)
 909  FORMAT(53H INPUT ERROR  --  LEVEL INDEX MUST BE .GE. 1 AND .LE.  
     11H, I2/)
 910  FORMAT(54H INPUT ERROR  --  SPIN QUANTUM NUMBER MUST BE .GE. 0.0/)
 911  FORMAT(41H INPUT ERROR  --  ENERGY MUST BE .GE. 0.0/)
 912  FORMAT(51H INPUT ERROR  --  IPAR(N) MUST BE EQUAL 1 FOR EVEN  
     128HPARITY AND -1 FOR ODD PARITY/)
 913  FORMAT(53H INPUT ERROR  --  MULTIPOLARITY MUST BE .GE. 1 AND .L
     14HE. 6/)
 914  FORMAT(50H INPUT ERROR  --  NGMAX MUST BE .GE. 1 AND .LE. 10/)
 915  FORMAT(53H INPUT ERROR  --  GROUP INDEX MUST BE .GE. 1 AND .LE.
     13H 10/)
 916  FORMAT(53H INPUT ERROR  --  NSTART(I) AND NSTOP(I) MUST BE .GE.
     112H 1 AND .LE. ,I2/)
 917  FORMAT(53H INPUT ERROR  --  NSTOP(I) MUST BE GREATER THAN NSTAR
     14HT(I)/)
 918  FORMAT(43H INPUT ERROR  --  EMMAX(I) MUST BE .GE. 0.0/)
 919  FORMAT(48H INPUT ERROR  --  IEXCIT(I) MUST BE EQUAL 1 (FOR
     158H PROJECTILE EXCITATION) OR EQUAL 2 (FOR TARGET EXCITATION)/)
 920  FORMAT(42H INPUT ERROR  --  MAXIMUM NUMBER OF LEVELS
     120H IN EACH GROUP IS 11)
 921  FORMAT(38H INPUT ERROR  --  NTIME MUST BE .GT. 0)
 922  FORMAT(54H INPUT ERROR  --  DTHETA MUST BE POSITIVE AND .LT. 180)
      END
      SUBROUTINE INTG
!
!     THIS ROUTINE INTEGRATES THE COUPLED DIFFERENTIAL EQUATIONS
!
      INTEGER SSTART,SSTOP,OUAMP,OUPROW
      COMPLEX AMP,AMPDOT,AMPP,F,Q1,RK1,RK2,RK3
      LOGICAL ERR
      DIMENSION PROB(600)
      DIMENSION Q1(600,4),AMPP(600,4),F(600,4,4),AMPDOT(600,4)
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL12/LMX,IR1,IR2,N1,N2
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL24/AMP(600,4)
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL39/UP,DW,ISTEP,D2W
      COMMON/BL40/SSTART(31),SSTOP(30)
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL53/P(25)
	common/output/iop
      DOUBLEPRECISION FZR,FZI,FZ        !*************************
!
!     INITIAL CONDITIONS FOR INTEGRATION
      KAST = 0
      ISTEPS = 0
!     ISTEPS COUNTS ACTUAL NUMBER OF STEPS
      INTERV = INTIN
      W = -UP
!     INITIAL VALUES OF AMPLITUDES  AMP(W=-UP)
      DO 110 K=1,IEXNUM
      LMX = LMAX(K)
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
      DO 105 L=1,LMX
      DO 100 IR=IR1,IR2
      AMP(IR,L) = (0.0,0.0)
      IF(L.EQ.IR-IR1+1) AMP(IR,L) = (1.0,0.0)
 100  CONTINUE
 105  CONTINUE
 110  CONTINUE
!     CONSTANTS USED IN RUNGE-KUTTA-GILL EQUATIONS
      B1=0.5857864
      C1=0.1213204
      B2=3.4142136
      C2=-4.1213204
!
!     INITIAL TIMING OF INTEGRATION
      CALL ZCLOCK(TIME1)
!      ASSIGN 360 TO ITI
      IF(OUPROW.EQ.0) GOTO 120
!
!     HEADING FOR PRINT-OUT OF PROBABILITIES
      write(50,900)(N,N=1,NMAX)
      P(1)=1.0
      DO 115 N=2,NMAX
 115  P(N) = 0.0
      N1 = NSTART(IP)
      IF(IEXNUM.EQ.2) P(N1)=1.0
      PTOT = P(1) + P(N1)
      write(50,902) W,(P(N),N=1,NMAX)
!
!     ******************************************************************
!     THE RUNGE-KUTTA-GILL INTEGRATION PROCEDURE
!     ******************************************************************
!
 120  CONTINUE
!     COMPUTATION OF START VALUES OF THE DERIVATIVES
      CALL Q(W)
      DO 145  K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 130
      DO 125 L=1,LMX
      DO 125 IR=IR1,IR2
      F(IR,L,1) = AMPDOT(IR,L)
 125  CONTINUE
      GOTO 145
 130  DO 140 L=1,LMX
      DO 140 N=N1,N2
      IR = SSTART(N) - 1
 135  IR = IR + 1
      F(IR,L,1) = AMPDOT(IR,L)
      IF(CAT(IR,3).LT.-0.1)GOTO 135
 140  CONTINUE
 145  CONTINUE
!     ******************************************************************
!     COMPUTATION OF AMPLITUDES ACCORDING TO EQUATION (II.7.3A)
      DO 275 NAM=2,4
      DO 170 K=1,IEXNUM
      CALL PREP3(K)
      IF(SPIN(N1).EQ.0.)GOTO 155
      DO 150 L=1,LMX
      DO 150 IR=IR1,IR2
      Q1(IR,L) = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + Q1(IR,L)
 150  CONTINUE
      GOTO 170
 155  DO 165 L=1,LMX
      DO 165 N=N1,N2
      IR = SSTART(N) - 1
 160  IR = IR + 1
      Q1(IR,L) = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + Q1(IR,L)
!     MAKE USE OF SYMMETRY RELATION (EQUATION (I.2.30))
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMP(IR1,L) = IFAC(N)*AMP(IR,L)
      IF(CAT(IR,3).LT.-0.1)GOTO 160
 165  CONTINUE
 170  CONTINUE
!     COMPUTATION OF AMPLITUDES ACCORDING TO EQUATION (II.7.3B)
      W = W + DW
      CALL Q(W)
      DO 195 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 180
      DO 175 L=1,LMX
      DO 175 IR=IR1,IR2
      RK1 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + B1*(RK1-Q1(IR,L))
      Q1(IR,L) = B1*RK1 + C1*Q1(IR,L)
 175  CONTINUE
      GOTO 195
 180  DO 190 L=1,LMX
      DO 190 N=N1,N2
      IR = SSTART(N) - 1
 185  IR = IR + 1
      RK1 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + B1*(RK1-Q1(IR,L))
      Q1(IR,L) = B1*RK1 + C1*Q1(IR,L)
!     MAKE USE OF SYMMETRIE RELATION (EQUATION (I.2.30))
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMP(IR1,L) = IFAC(N)*AMP(IR,L)
      IF(FLOAT(MIR).LT.-0.1)GOTO 185
 190  CONTINUE
 195  CONTINUE
!     ******************************************************************
!     COMPUTATION OF AMPLITUDES ACCORDING TO EQUATION (II.7.3C)
      DO 220 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 205
      DO 200 L=1,LMX
      DO 200 IR=IR1,IR2
      RK2 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + B2*(RK2-Q1(IR,L))
      Q1(IR,L) = B2*RK2 + C2*Q1(IR,L)
 200  CONTINUE
      GOTO 220
 205  DO 215 L=1,LMX
      DO 215 N=N1,N2
      IR = SSTART(N) - 1
 210  IR = IR + 1
      RK2 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + B2*(RK2-Q1(IR,L))
      Q1(IR,L) = B2*RK2 + C2*Q1(IR,L)
!     MAKE USE OF SYMMETRIE RELATION (EQUATION (I.2.30))
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMP(IR1,L) = IFAC(N)*AMP(IR,L)
      IF(FLOAT(MIR).LT.-0.1)GOTO 210
 215  CONTINUE
 220  CONTINUE
!     ******************************************************************
!     COMPUTATION OF AMPLITUDES ACCORDING TO EQUATION (II.7.3D)
      W = W + DW
      CALL Q(W)
      DO 245 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 230
      DO 225 L=1,LMX
      DO 225 IR=IR1,IR2
      RK3 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + RK3/3.0 - 2.0*Q1(IR,L)/3.0
 225  CONTINUE
      GOTO 245
 230  DO 240 L=1,LMX
      DO 240 N=N1,N2
      IR = SSTART(N) - 1
 235  IR = IR + 1
      RK3 = DW*AMPDOT(IR,L)
      AMP(IR,L) = AMP(IR,L) + RK3/3.0 - 2.0*Q1(IR,L)/3.0
!     MAKE USE OF SYMMETRIE RELATION (EQUATION (I.2.30))
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMP(IR1,L) = IFAC(N)*AMP(IR,L)
      IF(FLOAT(MIR).LT.-0.1)GOTO 235
 240  CONTINUE
 245  CONTINUE
!     ******************************************************************
!     STORING OF DERIVATIVES IN ARRAY F
      DO 270 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 255
      DO 250 L=1,LMX
      DO 250 IR=IR1,IR2
      F(IR,L,NAM) = AMPDOT(IR,L)
 250  CONTINUE
      GOTO 270
 255  DO 265 L=1,LMX
      DO 265 N=N1,N2
      IR = SSTART(N) - 1
 260  IR = IR + 1
      F(IR,L,NAM) = AMPDOT(IR,L)
      IF(CAT(IR,3).LT.-0.1)GOTO 260
 265  CONTINUE
 270  CONTINUE
      ISTEPS = ISTEPS + 1
      KAST = KAST + 1
 275  CONTINUE
!     WE NOW HAVE THE FOUR START VALUES FOR THE DERIVATIVES AND CAN
!     PROCEED BY THE FASTER ADAMS-MOULTON-PROCEDURE
!
!     ******************************************************************
!     THE ADAMS-MOULTON-PROCEDURE
!     ******************************************************************
!
 280  CONTINUE
!     COMPUTATION OF AMPLITUDES AMPP ACCORDING TO EQUATION (II.7.6)
      DO 305 K=1,IEXNUM
      CALL PREP3(K)
      IF(SPIN(N1).EQ.0.)GOTO 290
      DO 285 L=1,LMX
      DO 285 IR=IR1,IR2
      AMPP(IR,L) = AMP(IR,L) + DW/12.0*(55.0*F(IR,L,4)-59.0*F(IR,L,3)
     1+37.0*F(IR,L,2)-9.0*F(IR,L,1))
 285  CONTINUE
      GOTO 305
 290  DO 300 L=1,LMX
      DO 300 N=N1,N2
      IR = SSTART(N) - 1
 295  IR = IR + 1
      AMPP(IR,L) = AMP(IR,L) +DW/12.0*(55.0*F(IR,L,4)-59.0*F(IR,L,3)
     1+37.0*F(IR,L,2)-9.0*F(IR,L,1))
!     USING OF THE SYMMETRY RELATION EQUATION (I.2.30)
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMPP(IR1,L) = IFAC(N)*AMPP(IR,L)
      IF(FLOAT(MIR).LT.-0.1)GOTO 295
 300  CONTINUE
 305  CONTINUE
!     ******************************************************************
!     COMPUTATION OF AMPLITUDES AMP ACCORDING TO EQUATION (II.7.7)
      W = W + DW + DW
      KAST = KAST + 1
      ISTEPS = ISTEPS + 1
      CALL Q(W)
      DO 330 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMPP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 315
      DO 310 L=1,LMX
      DO 310 IR=IR1,IR2
      AMP(IR,L) = AMP(IR,L) + DW/12.0*(9.0*AMPDOT(IR,L)+19.0*F(IR,L,4)
     1-5.0*F(IR,L,3)+F(IR,L,2))
 310  CONTINUE
      GOTO 330
 315  DO 325 L=1,LMX
      DO 325 N=N1,N2
      IR = SSTART(N) - 1
 320  IR = IR + 1
      AMP(IR,L) = AMP(IR,L) + DW/12.0*(9.0*AMPDOT(IR,L)+19.0*F(IR,L,4)
     1-5.0*F(IR,L,3)+F(IR,L,2))
!     MAKE USE OF SYMMETRIE RELATION (EQUATION (I.2.30))
      MIR = CAT(IR,3)
      IR1 = IR - 2*MIR
      AMP(IR1,L) = IFAC(N)*AMP(IR,L)
      IF(FLOAT(MIR).LT.-0.1)GOTO 320
 325  CONTINUE
 330  CONTINUE
!     ******************************************************************
      DO 355 K=1,IEXNUM
      CALL PREP3(K)
      CALL AMPDER(AMP,AMPDOT,K)
      IF(SPIN(N1).EQ.0.)GOTO 340
      DO 335 L=1,LMX
      DO 335 IR=IR1,IR2
      F(IR,L,1) = F(IR,L,2)
      F(IR,L,2) = F(IR,L,3)
      F(IR,L,3) = F(IR,L,4)
      F(IR,L,4) = AMPDOT(IR,L)
 335  CONTINUE
      GOTO 355
 340  DO 350 L=1,LMX
      DO 350 N=N1,N2
      IR = SSTART(N) - 1
 345  IR = IR + 1
      F(IR,L,1) = F(IR,L,2)
      F(IR,L,2) = F(IR,L,3)
      F(IR,L,3) = F(IR,L,4)
      F(IR,L,4) = AMPDOT(IR,L)
      IF(CAT(IR,3).LT.-0.1)GOTO 345
 350  CONTINUE
 355  CONTINUE
!     ******************************************************************
!     ******************************************************************
      IF(ISTEPS.LT.10)GOTO 370
!
!     TIMING OF INTEGRATION AFTER FIRST TEN STEPS
 360  CALL ZCLOCK(TIME2)
!      TLAPSE = TIME2-TIME1
      TLAPSE = 0.0
      ESTTIM = TLAPSE*FLOAT(ISTEP)/10.
c This code (ISTEP = 9) was introduced to fix an outdated GOTO label issue
      ISTEP = 9
!      write(50,926) ESTTIM
      IF(ESTTIM.LT.FLOAT(NTIME))GOTO 370
      write(50,928)  ! error message
      GOTO 850
 370  IF(W+DW.GT.UP) GOTO 405
!
!     ACCURACY CONTROL
      IF(KAST.LT.INTERV) GOTO 280
!     FIND LARGEST  AMPP - AMP
      FF=0.0
      DO 390 K=1,IEXNUM
      LMX = LMAX(K)
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
      DO 385 L=1,LMX
      DO 380 IR=IR1,IR2
      FZR = REAL(AMPP(IR,L)) - REAL(AMP(IR,L))
      FZI = AIMAG(AMPP(IR,L)) - AIMAG(AMP(IR,L))
      FZ=(SQRT(FZR*FZR+FZI*FZI))/14.0
      IF(FZ.GT.FF) FF=FZ
 380  CONTINUE
 385  CONTINUE
 390  CONTINUE
      ACC050 = ACCUR/50.0
      IF (FF .LT. ACC050) GOTO 395
      IF (FF .GT. ACCUR) GOTO 400
      GOTO 405
 395  DW=2.0*DW
      INTERV=INTERV/2
      IF(INTERV.EQ.0) INTERV = 1
      D2W=2.*DW
      if(iop.eq.1)write(50,904) W,D2W
      GOTO 405
 400  CONTINUE
      DW=DW/2.0
      INTERV=2*INTERV
      D2W=2.*DW
      if(iop.eq.1)write(50,906) W,D2W
      KAST = 0
      GOTO 120
!
!     THE EXCITATION PROBABILITIES DURING INTEGRATION
 405  DO 435 K=1,IEXNUM
      N1 = 1
      IF(K.EQ.2) N1=NSTART(IP)
      LLMAX = 2*(SPIN(N1)+1.1)
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
      DO 430 IR=IR1,IR2
      PROB(IR) = 0.0
!     SUMMATION OVER GROUND STATE POLARIZATIONS
      L = 1
      DO 425 LL=2,LLMAX,2
      IF(LL-LLMAX)410,415,425
 410  FAC = 2.0/(2.0*SPIN(N1)+1.0)
      GOTO420
 415  FAC = 1.0/(2.0*SPIN(N1)+1.0)
 420  FZR = REAL(AMP(IR,L))
      FZI = AIMAG(AMP(IR,L))
      PROB(IR) = PROB(IR) + FAC * (FZR*FZR + FZI*FZI)
      L = L + 1
 425  CONTINUE
 430  CONTINUE
 435  CONTINUE
      DO 445 N=1,NMAX
      P(N) = 0.0
      IR1 = SSTART(N)
      IR2 = SSTOP(N)
      DO 440 IR=IR1,IR2
 440     P(N) = P(N) + PROB(IR)
 445  CONTINUE
!
!     TOTAL PROBABILITY
      PTOTP = 0.0
      PTOTT = 0.0
      DO 475 K=1,IEXNUM
      IF(K.EQ.2)GOTO 450
      N1 = 1
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IGROUP = 1
      GOTO 455
 450  N1 = NSTART(IP)
      N2 = NMAX
      IGROUP = IP
 455  IEXC = IEXCIT(IGROUP)
      IF(IEXC.EQ.2)GOTO 465
      DO 460 N=N1,N2
 460  PTOTP = PTOTP + P(N)
      GOTO 475
 465  DO 470 N=N1,N2
 470  PTOTT = PTOTT + P(N)
 475  CONTINUE
!
!     UNITARITY CHECK OF THE TOTAL PROBABILITY
      DO 485 K=1,IEXNUM
      IGROUP = 1
      IF(K.EQ.2) IGROUP=IP
      IEXC = IEXCIT(IGROUP)
      IF(IEXC.EQ.2)GOTO 480
      ABW = ABS(PTOTP-1.0)/20.0
      IF(ABW.LT.ACCUR)GOTO 485
      write(50,908) W,PTOTP  ! warning
      GOTO 485
 480  ABW = ABS(PTOTT-1.0)/20.0
      IF(ABW.LT.ACCUR)GOTO 485
      write(50,910) W,PTOTT  ! warning
 485  CONTINUE
      IF(OUPROW.EQ.0)GOTO 490
!
!     PRINT-OUT OF EXCITATION PROBABILITIES FOR CURRENT VALUE OF W
      PTOT = PTOTP + PTOTT
      write(50,902) W,(P(N),N=1,NMAX)
      write(50,912) PTOT
 490  KAST=0
      IF(W+DW.GT.UP) GOTO 500
      IF(FF.LT.ACC050) GOTO 120
      GOTO 280
 500  CONTINUE
!
!     INTEGRATION COMPLETED
!
      if(iop.eq.1)write(50,914) ISTEPS
      IF(OUAMP.EQ.0)GOTO 550
!
!     PRINT-OUT OF THE FINAL AMPLITUDES AMP(W=+UP)
      DO 545 K=1,IEXNUM
      LMX = LMAX(K)
      IF(K.EQ.2)GOTO 510
      N1 = 1
      IGROUP = 1
      GOTO 515
 510  N1 = NSTART(IP)
      IGROUP = IP
 515  IEXC = IEXCIT(IGROUP)
      DO 540 L=1,LMX
      IR1 = SSTART(N1)
      IRL = IR1 + L - 1
      IF(IEXC.EQ.2)GOTO 520
      if(iop.eq.1)write(50,916) CAT(IRL,3)
      GOTO 525
 520  if(iop.eq.1)write(50,918) CAT(IRL,3)
 525  if(iop.eq.1)write(50,920)
      VAL = N1
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
      DO 540 IZR=IR1,IR2
      POP=(REAL(AMP(IZR,L)))**2+(AIMAG(AMP(IZR,L)))**2
      IF(CAT(IZR,1).LE.VAL)GOTO 530
      VAL = CAT(IZR,1)
      if(iop.eq.1)write(50,922)
 530  if(iop.eq.1)WRITE(50,924) (CAT(IZR,LC),LC=2,3), AMP(IZR,L), POP
 540  CONTINUE
 545  CONTINUE
 550  RETURN
!
!     ERROR EXIT
!
 850  ERR = .TRUE.
      RETURN
!
 900  FORMAT(1H0,5X,1HW4X,10(3X,2HP(I2,1H)4X),/3X,
     111(3X,2HP(I2,1H)4X),/3X,11(3X,2HP(I2,1H)4X))
 902  FORMAT(1H0,F10.3,10E12.4,/3X,11E12.4,/3X,11E12.4)
 904  FORMAT(8H0AT W = F7.3,36H, STEP WIDTH WAS DOUBLED TO BE D2W= F8.5)
 906  FORMAT(8H0AT W = F7.3,35H, STEP WIDTH WAS HALVED TO BE D2W= F8.5)
 908  FORMAT(1H0,26H  - -  WARNING  - - AT W= ,F6.3,10X,5HPTOT  
     116HFOR PROJECTILE =F10.6,3X,32HERROR IN PTOT EXCEEDS 20 X ACCUR)
 910  FORMAT(1H0,26H  - -  WARNING  - - AT W= ,F6.3,10X,
     117HPTOT FOR TARGET =F10.7,3X,32HERROR IN PTOT EXCEEDS 20 X ACCUR)
 912  FORMAT(7H PTOT =E11.4,//)
 914  FORMAT(34H0ACTUAL NUMBER OF STEPS, ISTEPS = I4)
 916  FORMAT(13H1INITIAL M = F4.1,20X,21HPROJECTILE AMPLITUDES)
 918  FORMAT(13H1INITIAL M = F4.1,20X,17HTARGET AMPLITUDES)
 920  FORMAT (1H0,1X4HSPIN2X12HMAG.QUAN.NO.1X14HREAL AMPLITUDE1X  
     114HIMAG AMPLITUDE3X10HPOPULATION)
 922  FORMAT(1H0)
 924  FORMAT(1XF5.1,F9.1,3X3E15.4)
 926  FORMAT(18H0ESTIMATED TIME = F11.4,4H SEC)
 928  FORMAT(45H0 EXCEEDS ALLOWED TIME - EXECUTION TERMINATED)
      END
      SUBROUTINE LAISUM(AMP,AMPDOT,IR,N,LMX)
!
!     THIS ROUTINE COMPUTES AMPDOT(IR,L)
!
      COMPLEX AMP,AMPDOT,RC,CI
      COMPLEX CQU1,CQU2,CQU3,CQU4,CQU5,CQU6,CQU7,CQU8,CQU9,CQU10,CQU11,
     1CQU12
      INTEGER SSTART,SSTOP
      DIMENSION AMP(600,4),AMPDOT(600,4)
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL5/NZ
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON/BL13/CQU1(7,25,25),CQU2(7,25,25),CQU3(7,25,25)
      COMMON/BL14/CQU4(7,25,25),CQU5(7,25,25),CQU6(7,25,25)
      COMMON/BL15/CQU7(7,25,25),CQU8(7,25,25),CQU9(7,25,25)
      COMMON/BL16/CQU10(7,25,25),CQU11(7,25,25),
     1CQU12(7,25,25)
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL40/SSTART(31),SSTOP(30)
      DATA CI/(0.0,1.0)/
!
      RMIR = CAT(IR,3)
      DO 100 L=1,LMX
 100  AMPDOT(IR,L) = (0.0,0.0)
      DO 580 I1=1,LAMMAX
      LAM = LAMDA(I1)
      LA = LAM
      IF(LAM.GT.6) LAM=LAM-6
      LD = LDNUM(LA,N)
      IF(LD.EQ.0)GOTO 580
      DO 560 I2=1,LD
      M = LEAD(N,I2,LA)
      ISMIN = 0
      IS1 = SSTART(M)
      ISPLUS = IFIX(RMIR-CAT(IS1,3))-LAM
      IF(ISPLUS.GE.0)GOTO 150
      ISMIN = ISPLUS
      ISPLUS = 0
 150  IS2 = IS1+ISPLUS-1
      MRANGE = 2*LAM+1+ISMIN
      IF(IS2+MRANGE.GT.SSTOP(M)) MRANGE=SSTOP(M)-IS2
      IF(MRANGE.LE.0)GOTO 560
      DO 540 I3=1,MRANGE
      IS = IS2+I3
      NZ = NZ + 1
      Z = ZETA(NZ)
      RMU = CAT(IS,3) - RMIR
      MUA = ABS(RMU) + 1.1
      DO 520 L=1,LMX
!     COMPUTATION OF THE PARTIAL SUM FOR MULTIPOLARITY LA
      GOTO(210,220,230,240,250,260,310,320,330,340,350,360),LA
 210  RC = CQU1(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 220  RC = CQU2(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 230  RC = CQU3(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 240  RC = CQU4(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 250  RC = CQU5(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 260  RC = CQU6(MUA,N,M)*AMP(IS,L)*Z
      GOTO 400
 310  RC = CQU7(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
      GOTO 400
 320  RC = CQU8(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
      GOTO 400
 330  RC = CQU9(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
      GOTO 400
 340  RC =CQU10(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
      GOTO 400
 350  RC =CQU11(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
      GOTO 400
 360  RC =CQU12(MUA,N,M)*AMP(IS,L)*Z
      IF(RMU.LT.-0.1) RC=-RC
 400  AMPDOT(IR,L) = AMPDOT(IR,L) - CI*RC
 520  CONTINUE
 540  CONTINUE
 560  CONTINUE
 580  CONTINUE
      RETURN
      END
      SUBROUTINE LEXEM(A,X,N,MODE,IERR)

!     SUBROUTINE LEXEM SCANS THE 72 CHARACTERS STORED IN THE FIELD
!     A(72). IF THE CHARACTERS ARE INTERPRETED AS DIGITS OF ONE OR
!     MORE NUMBERS, THESE NUMBERS ARE STORED AS AN ELEMENT OF THE
!     ARRAY X. THE SCANNING IS STOPPED BY A CHARACTER INTERPRETED
!     AS START OF A TEXT-STRING.
!         A IS THE INPUT FIELD FOR 72 CHARACTERS.
!         X IS THE OUTPUT FIELD FOR THE DETECTED NUMBERS.
!         N TELLS,  HOW MANY NUMBERS HAVE BEEN DETECTED IN THE ARRAY A.
!         MODE = 0 ARRAY A CONTAINS ONLY NUMBERS AND NO TEXT.
!            .GE.1 ARRAY A CONTAINS TEXT STARTING AT THE LOCATION
!                   A(MODE).
!     BY R. ZIMMERMANN, MUNICH,1979

      DIMENSION X(72),A(72),B(16)
      DATA B/1H0,1H1,1H2,1H3,1H4,1H5,1H6,1H7,1H8,1H9,
     11H ,1H,,1H+,1H-,1H.,1HE/
      IERR=0
      MODE=0
      I=0
      N=0
      IZ=1
      SIGM=1.0
      XM=0.0
      SIGE=1.0
      XE=0.0
   90 I=I+1
      IF (IZ.EQ.1) NM=I
      IF (I.GE.73) GOTO 300
      DO 92 K=1,16
      IF (A(I).EQ.B(K)) GOTO 94
   92 CONTINUE
      GOTO 100
   94 CONTINUE
      GOTO(1,1,1,1,1,1,1,1,1,1,2,3,4,4,5,6),K

!HARACTER IS ONE DIGIT OF A NUMBER
1     XX=K-1
      GOTO(21,22,23,24,25,26),IZ

!     START OF A NUMBER, FIRST DIGIT DETECTED
   21 NM=I
      SIGM=+1.0
      XM=XX
      IZ=3
      GOTO 90

!     A SIGN WAS PRECEEDING THE FIRST DIGIT
   22 XM=XX
      IZ=3
      GOTO 90

!     ONE OF THE OTHER DIGITS BEFORE THE DECIMAL POINT
   23 XM=10.0*XM+XX
      GOTO 90

!     ONE OF THE DIGITS AFTER THE DECIMAL POINT
   24 XME=10.0*XME
      XM=XM+XX/XME
      GOTO 90

!     FIRST DIGIT OF THE EXPONENT
   25 SIGE=+1.0
      XE=XX
      IZ=6
      GOTO 90

!     ONE OF THE OTHER DIGITS OF THE EXPONENT
   26 XE=10.0*XE+XX
      GOTO 90

!HARACTER IS A BLANK
2     CONTINUE
      GOTO(90,100,200,200,100,200),IZ

!HARACTER IS A COMMA
3     CONTINUE
      GOTO(100,100,200,200,100,200),IZ

!HARACTER IS THE SIGN OF A NUMBER
4     CONTINUE
      GOTO(40,100,100,100,45,100),IZ
   40 IZ=2
      NM=I
      SIGM=+1.0
      IF (A(I).EQ.B(14)) SIGM=-1.0
      GOTO 90
   45 SIGE=+1.0
      IF (A(I).EQ.B(14)) SIGE=-1.0
      IZ=6
      GOTO 90

!HARACTER IS A DECIMAL POINT
5     CONTINUE
      GOTO(50,51,52,100,100,100),IZ
   50 SIGM=+1.0
      NM=I
   51 XM=0.0
   52 IZ=4
      XME=1.0
      GOTO 90

!HARACTER IS AN E, THE FOLLOWING DIGITS ARE THE EXPONENT
6     CONTINUE
      GOTO(100,100,60,60,100,100),IZ
   60 IZ=5
      XE=0.0
      GOTO 90

!     TEXT,STOP SCANNING
  100 MODE=NM
      RETURN

!     DELIMITER, STORE THE DETECTED NUMBER AS THE N-TH ELEMENT
!     OF THE ARRAY X
  200 N=N+1
      X(N)=SIGM*XM*10.0**(SIGE*XE)
      NM=I
      IZ=1
      SIGM=1.0
      XM=0.0
      SIGE=1.0
      XE=0.0
      GOTO 90

!     ERROR EXIT
  300 IF (IZ.EQ.1) RETURN
      IERR=1
      GOTO 100
!     RETURN
      END
      SUBROUTINE LSLOOP(IR,N,NZ)
!
!     THIS ROUTINE COMPUTES THE ZETA-ARRAY
!
      INTEGER SSTART,SSTOP
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL6/PSI(25,25,12)
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL40/SSTART(31),SSTOP(30)
!
!     LAMDA - LOOP  AND  IS - LOOP  FOR THE INPUT-VALUE IR
      SPINR = CAT(IR,2)
      RMIR = CAT(IR,3)
      DO 400 I1=1,LAMMAX
      LAM = LAMDA(I1)
      LA = LAM
      IF(LAM.GT.6) LAM=LAM-6
      RLAM = FLOAT(LAM)
      SSQRT = SQRT(2.0*RLAM+1.0)
      LD = LDNUM(LA,N)
      IF(LD.EQ.0)GOTO 400
      DO 300 I2=1,LD
      M = LEAD(N,I2,LA)
      ISMIN = 0
      SPINS = SPIN(M)
      IS1 = SSTART(M)
      ISPLUS = IFIX(RMIR-CAT(IS1,3))-LAM
      IF(ISPLUS.GE.0)GOTO 100
      ISMIN = ISPLUS
      ISPLUS = 0
 100  IS2 = IS1+ISPLUS-1
      MRANGE = 2*LAM+1+ISMIN
      IF(IS2+MRANGE.GT.SSTOP(M)) MRANGE = SSTOP(M)-IS2
      IF(MRANGE.LE.0)GOTO 300
      DO 200 I3=1,MRANGE
      IS = IS2+I3
      RMIS = CAT(IS,3)
      G1 = -RMIS
      G2 = RMIS - RMIR
      NZ = NZ + 1
      IF(NZ.GT.NZMAX) GOTO 200
      IIEX = SPINS - RMIS
      PHZ = (-1.0)**IIEX
!     write(50,910)SPINS,RLAM,SPINR
!     write(50,910)G1,G2,RMIR
      TTT=THREEJ(SPINS,G1,RLAM,G2,SPINR,RMIR)
!     write(50,920)TTT
      ZETA(NZ)=PHZ*PSI(N,M,LA)*SSQRT*TTT
!     write(50,900) NZ,IR,IS,LA,ZETA(NZ)
 200  CONTINUE
 300  CONTINUE
 400  CONTINUE
      RETURN
!
 900  FORMAT(1H ,4HNZ =I4,6X,4HIR =I4,6X,4HIS =I4,6X,5HLAM =I2,6X,
     16HZETA =F12.4)
  910 FORMAT(3F10.1)
  920 FORMAT(35X,F10.6)
      END
      SUBROUTINE MAT
!
!     THIS ROUTINE CHECKS THE INPUT OF MATRIX ELEMENTS MEM(N,M,LAMDA)
!     THE MEM-MATRIX IS SYMMETRIZED AS NEEDED
!
      REAL MEM,MTR
      LOGICAL ERR
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL32/NMAX,NDIM
!
      DO 500 N=1,NMAX
      DO 500 M=N,NMAX
      DO 400 I=1,LAMMAX
      LAM = LAMDA(I)
      LA = LAM
      IF(LAM.GT.6) LA=LAM-6
      MTR=MEM(N,M,LAM)
      IF(MTR.EQ.0.0) GOTO 300
!
!     TRIANGLE RELATION
      IF(ABS(SPIN(N)-LA).LE.SPIN(M).AND.SPIN(M).LE.(SPIN(N)+LA))GOTO 140
      MEM(N,M,LAM)=0.0
!
!     PARITY CONSERVATION
 140  IDP = 1
      IF(IPAR(N).NE.IPAR(M)) IDP=-1
      L = LA
      IF(LAM.GT.6) L=LA+1
      IF(IDP.EQ.(-1)**L)GOTO 150
      MEM(N,M,LAM)=0.0
 150  IF(M.EQ.N)GOTO 400
!
!     SYMMETRISATION OF THE MEM-MATRIX
 300  FAC = (-1.)**IFIX(ABS(SPIN(N)-SPIN(M))+0.001)
      MEM(M,N,LAM) = FAC*MTR
 400  CONTINUE
 500  CONTINUE
      RETURN
      END
      SUBROUTINE MATROT
!
!     THIS SUBROUTINE COMPUTES THE MATRIX ELEMENTS
!     ACCORDING TO A ROTATIONAL MODEL WITH INTRINSIC PARAMETERS
!     INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
!     DEFINED IN BOHR AND MOTTELSON, VOL II, PG.155
!
      REAL INTM1
      REAL INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      REAL MEM,MULT
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL32/NMAX,NDIM
      COMMON/BL36/INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
!
      K1=0
      K2=0
      K3=0
      K4=0
      K5=0
      K6=0
      K7=0
      PI=3.1415926
      FPY1=1.0/SQRT(4.0*PI/3.0)
      FPY2=1.0/SQRT(16.0*PI/5.0)
      FPY1=1.0
      FPY2=1.0
      DO 600 N = 1,NMAX
      AJ1 = SPIN(N)
      AM1 = BANDK(N)
      ROOTN = SQRT(2.0*SPIN(N) + 1.0)
      DO 600 M = N,NMAX
      AJ3 = SPIN(M)
      ROOTM = SQRT(SPIN(M)*2.0 + 1.0)
      IEX=ABS(SPIN(N)+BANDK(M))+0.001
      DELK=BANDK(M)-BANDK(N)
      AM3=-BANDK(M)
      PHZ = (-1.0)**IEX
      IF(INTE2.EQ.0.0)GOTO 200
!
!     COMPUTATION OF E2-MATRIX ELEMENT MEM(N,M,2)
      LAM = 2
      IF(ABS(DELK).GT.2.0)GOTO 200
      IF(IPAR(N).NE.IPAR(M))GOTO 200
      TRJ2=THREEJ(AJ1,AM1,2.00,DELK,AJ3,AM3)
      MEM(N,M,2)=PHZ*ROOTN*ROOTM*INTE2*MULT(N,M,LAM)*TRJ2*FPY2
      IF(MEM(N,M,2).EQ.0.0)GOTO 200
      I = 1
      K2 = K2 + 1
      IF(K2.EQ.1)GOTO 400
 200  IF(INTE3.EQ.0.0)GOTO 300
!
!     COMPUTATION OF E3-MATRIX ELEMENT MEM(N,M,3)
      LAM = 3
      IF(ABS(DELK).GT.3.0)GOTO 300
      IF(IPAR(N).EQ.IPAR(M))GO TO 300
      TRJ3=THREEJ(AJ1,AM1,3.00,DELK,AJ3,AM3)
      MEM(N,M,3)=-PHZ*ROOTN*ROOTM*INTE3*TRJ3
      IF(MEM(N,M,3).EQ.0.0)GOTO 300
      I = 2
      K3 = K3 + 1
      IF(K3.EQ.1)GOTO 400
 300  IF(INTM1.EQ.0.0)GOTO 600
!
!     COMPUTATION OF M1 MATRIX-ELEMENT MEM(N,M,7)
      LAM=7
      IF(ABS(DELK).GT.1.0) GO TO 600
      IF(IPAR(N).NE.IPAR(M))GO TO 600
      TRJ7=THREEJ(AJ1,AM1,1.00,DELK,AJ3,AM3)
      MEM(N,M,7)=-PHZ*ROOTN*ROOTM*INTM1*TRJ7*FPY1
      IF(MEM(N,M,7).EQ.0.0)GO TO 600
      I = 3
      K7 = K7+1
      IF(K7.NE.1) GO TO 600
!
!     DETERMINATION OF  LAMMAX  AND  LAMDA(I)
 400  IF(LAM.EQ.LAMDA(1).OR.LAM.EQ.LAMDA(2).OR.LAM.EQ.LAMDA(3).OR.LAM.EQ
     1.LAMDA(4).OR.LAM.EQ.LAMDA(5).OR.LAM.EQ.LAMDA(6).OR.LAM.EQ.LAMDA(7)
     2.OR.LAM.EQ.LAMDA(8).OR.LAM.EQ.LAMDA(9).OR.LAM.EQ.LAMDA(10).OR.LAM.
     3EQ.LAMDA(11).OR.LAM.EQ.LAMDA(12))GOTO 500
      LAMMAX = LAMMAX + 1
      LAMDA(LAMMAX) = LAM
 500  IF(I.EQ.1)GOTO 200
      IF(I.EQ.2)GOTO 300
 600  CONTINUE
!
!     PRINT-OUT OF ROTATIONAL MODEL PARAMETERS AND OF MULT-MATRIX
      write(50,900)
      write(50,902) INTM1,INTE1,INTE2,INTE3,INTE4,INTE5,INTE6
      RETURN
!
 900  FORMAT(47H0MATRIX ELEMENTS ARE CALCULATED FROM ROTATIONAL,
     122H MODEL WITH INTRINSIC /12H PARAMETERS,9X5HINTM19X
     26HINTE1 ,8X6HINTE2 ,8X6HINTE3 8X6HINTE4 8X6HINTE5 8X6HINTE6 )
 902  FORMAT(13X7(4XF11.4))
      END
      SUBROUTINE PREP1
!
!     THIS ROUTINE PREPARES THE INTEGRATION
!     IT COMPUTES XI-MATRIX,PSI-MATRIX,LEAD-MATRIX,SSTART- AND SSTOP-ARR
!
      INTEGER SSTART,SSTOP,OUXI,OUPSI
      LOGICAL ERR
      REAL MEM
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL6/PSI(25,25,12)
      COMMON /BL7/ZETA( 1200),NZMAX
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL32/NMAX,NDIM
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL40/SSTART(31),SSTOP(30)
      COMMON/BL41/XI(25,25)
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL54/DISTA
	common/output/iop
      DIMENSION ETAN(25),CPSI(12)
!
!     CRITICAL SCATTERING ANGLE IN CM SYSTEM
      DISTR = 1.20*(A1**0.33333 + A2**0.33333) + 4.0
      DISTA=0.0719949*(1.0+A1/A2)*ZP*ZT/EP
      D2A = 20.0*DISTA
      VINF = 0.0463365*SQRT(EP/A1)
      if(iop.eq.1)write(50,942) VINF,D2A
      IF(D2A.GT.DISTR) GOTO 100
      TCRIT=2.0* ASIN(DISTA*10./(DISTR-DISTA))*57.295779
      if(iop.eq.1)write(50,900) DISTR,TCRIT
!
!     APPROXIMATION OF THE VIRTUAL EXCITATION OF THE GIANT DIPOLE
!     RESONANCE BY DIPOLE POLARIZATION EFFECTS
!     SEE ALDER/WINTHER, "ELECTROMAGNETIC EXCITATION", APPENDIX J
!     NORTH-HOLLAND PUBL.CO., AMSTERDAM (1975)
 100  ZPOL = DIPOL*EP*A2/(ZT*ZT*(1.+A1/A2))
!
!     XI- MATRIX
      ETA=ZP*ZT*SQRT(A1/EP)/6.349770
      DO 110 M=1,NMAX
      DEP=(1.0+A1/A2)*EN(M)
      ZET=DEP/EP
      SZET=SQRT(1.0-ZET)
      ETAN(M)=ETA/SZET
 110  CONTINUE
      DO 120 N=1,NMAX
      DO 120 M=1,NMAX
      XI(N,M) = 99.9
 120  CONTINUE
      DO 150 I1=1,LAMMAX
      LAM = LAMDA(I1)
      DO 140 N=1,NMAX
      DO 130 M=1,NMAX
      IF( MEM(N,M,LAM).EQ.0.0 ) GOTO 130
      XI(N,M) = ETAN(N) - ETAN(M)
 130  CONTINUE
 140  CONTINUE
 150  CONTINUE
      IF(OUXI.EQ.0)GOTO 200
!     PRINT-OUT OF XI-MATRIX
      write(50,902)
      NN = 1
      IF(NMAX.GT.11) NN=NGMAX
      DO 190 I=1,NN
      M1 = NSTART(I)
      M2 = NSTOP(I)
      IF(NMAX.GT.11)GOTO 165
      M1 = 1
      M2 = NMAX
 165  write(50,906)(M,M=M1,M2)
      DO 170 N=1,NMAX
      write(50,908) N,(XI(N,M),M=M1,M2)
 170  CONTINUE
      write(50,904)
 190  CONTINUE
!
!     COMPUTATION OF LEAD-MATRIX AND LDNUM-MATRIX
 200  DO 250 I5=1,LAMMAX
      LAM = LAMDA(I5)
      DO 240 I1=1,NGMAX
      N1 = NSTART(I1)
      N2 = NSTOP(I1)
      DO 230 N=N1,N2
      J = 0
      DO 220 I2=1,NGMAX
      IF ( MASTER(I1,I2).EQ.0 ) GOTO 220
      M1 = NSTART(I2)
      M2 = NSTOP(I2)
      DO 210 M=M1,M2
      IF ( MEM(N,M,LAM).EQ.0.0 ) GOTO 210
      J = J + 1
      LEAD(N,J,LAM) = M
 210  CONTINUE
 220  CONTINUE
      LDNUM(LAM,N) = J
 230  CONTINUE
 240  CONTINUE
 250  CONTINUE
!
!     PSI- MATRIX
      AAZZ=1./(1.+A1/A2)/ZP/ZT
      CPSI(1) = 5.169286*AAZZ
      CPSI(2) = 14.359366*AAZZ*AAZZ
      CPSI(3) = 56.982577 *AAZZ**3
      CPSI(4) = 263.812653*AAZZ**4
      CPSI(5) =1332.409500*AAZZ**5
      CPSI(6) =7117.691577*AAZZ**6
      CPSI(7) = VINF*CPSI(1)/95.0981942
      CPSI(8) = VINF*CPSI(2)/95.0981942
      CPSI(9) = VINF*CPSI(3)/95.0981942
      CPSI(10)= VINF*CPSI(4)/95.0981942
      CPSI(11)= VINF*CPSI(5)/95.0981942
      CPSI(12)= VINF*CPSI(6)/95.0981942
      DO 290 I1=1,LAMMAX
      LAM = LAMDA(I1)
      LAM1 = LAM
      IF(LAM.GT.6) LAM1=LAM-6
      DO 280 I2=1,NGMAX
      Z = ZP
!     FOR PROJECTILE EXCITATION   Z = ZT
      IF(IEXCIT(I2).EQ.1) Z=ZT
      ZSQA = Z*SQRT(A1)
      N1 = NSTART(I2)
      N2 = NSTOP(I2)
      DO 270 N=N1,N2
      PP1 = (EP-(1.0+A1/A2)*EN(N))**0.25
      DO 270 M=1,NMAX
      IF(MEM(N,M,LAM).EQ.0.0)GOTO 260
      PP2 = (EP-(1.0+A1/A2)*EN(M))**0.25
      PSI(N,M,LAM)=CPSI(LAM)*ZSQA*(PP1*PP2)**(2*LAM1-1)*MEM(N,M,LAM)
      GOTO 270
 260  PSI(N,M,LAM) = 0.0
 270  CONTINUE
 280  CONTINUE
 290  CONTINUE
      IF(OUPSI.EQ.0)GOTO 350
!     PRINT-OUT OF PSI-MATRIX
      write(50,910)
      DO 340 I1=1,LAMMAX
      LAM = LAMDA(I1)
      IF(LAM.GT.6)GOTO 302
      write(50,912) LAM
      GOTO 303
 302  LA = LAM - 6
      write(50,938) LA
 303  NN = 1
      IF(NMAX.GT.11) NN=NGMAX
      DO 330 I=1,NN
      M1 = NSTART(I)
      M2 = NSTOP(I)
      IF(NMAX.GT.11)GOTO 305
      M1 = 1
      M2 = NMAX
 305  write(50,906) (M,M=M1,M2)
      DO 310 N=1,NMAX
      K = 0
      DO 307 M=M1,M2
      P = PSI(N,M,LAM)
      IF(P.NE.0..AND.ABS(P).LT.0.001) K=1
 307  CONTINUE
      IF(K.EQ.1)GOTO 308
      write(50,908) N,(PSI(N,M,LAM),M=M1,M2)
      GOTO 310
 308  write(50,940) N,(PSI(N,M,LAM),M=M1,M2)
 310  CONTINUE
      write(50,904)
 330  CONTINUE
 340  CONTINUE
!
!     CATALOG OF MAGNETIC SUBSTATES; SSTART- AND SSTOP-ARRAY
 350  IS = 1
      SSTART(1) = 1
      DO 390 I1=1,NGMAX
      N1 = NSTART(I1)
      N2 = NSTOP(I1)
      DO 380 N= N1,N2
      QUAN = SPIN(N)
      IF(QUAN.GT.EMMAX(I1))QUAN = EMMAX(I1)
      MSTOP = 2.0*QUAN + 1.0001
      QUAN = -QUAN
      DO 370 I = 1,MSTOP
      IF ( IS.GT.ICATMX ) GOTO 360
      CAT(IS,1) = N
      CAT(IS,2)= SPIN(N)
      CAT(IS,3) = QUAN
 360  QUAN = QUAN +1.0
      IS = IS + 1
 370  CONTINUE
      SSTART(N+1) = IS
      SSTOP(N) = IS - 1
 380  CONTINUE
 390  CONTINUE
      ISMAX = IS -1
      if(iop.eq.1)write(50,914)ISMAX
      IF(ISMAX.LE.ICATMX)GOTO 400
!     ERROR EXIT IF NUMBER OF MAGNETIC SUBSTATES IS TOO LARGE
      write(50,916) ICATMX
      GOTO 850
!     PRINTOUT OF SSTART ARRAY AND SSTOP ARRAY
 400  if(iop.eq.1)write(50,918) (SSTART(I),I=1,NMAX)
      if(iop.eq.1)write(50,920) (SSTOP(I),I=1,NMAX)
!
!     LMAX-, IRSTA- AND IRSTO-ARRAY
      LMAX(1) = SPIN(1) + 1.1
      IRSTA(1) = 1
      IF(IEXNUM.EQ.2)GOTO 410
      IRSTO(1) = ISMAX
      GOTO 420
 410  N1 = NSTART(IP)
      IRSTO(1) = SSTART(N1) - 1
      LMAX(2) = SPIN(N1) + 1.1
      IRSTA(2) = IRSTO(1) + 1
      IRSTO(2) = ISMAX
!
!     ZETA-ARRAY
 420  NZ = 0
      DO 500 K=1,IEXNUM
      N1 = 1
      IF(K.EQ.2) N1=NSTART(IP)
      IF(SPIN(N1).EQ.0.)GOTO 450
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
!     IR - LOOP FOR GROUND STATE SPIN .NE. 0
      DO 440 IR=IR1,IR2
      N = CAT(IR,1)
      CALL LSLOOP(IR,N,NZ)
 440  CONTINUE
      GOTO 500
 450  IF(K.EQ.2)GOTO 460
      N1 = 1
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      GOTO 470
 460  N1 = NSTART(IP)
      N2 = NMAX
!     IR - LOOP FOR GROUND STATE SPIN = 0
 470  DO 490 N=N1,N2
      IR = SSTART(N) - 1
 480  IR = IR + 1
      CALL LSLOOP(IR,N,NZ)
!     ZETA ARRAY IS PRODUCED IN THIS SUBROUTINE
      IF(CAT(IR,3).LT.-0.1)GOTO 480
 490  CONTINUE
 500  CONTINUE
      if(iop.eq.1)write(50,922)NZ
!     ERROR EXIT IF NUMBER OF ELEMENTS IN ZETA-ARRAY IS TOO LARGE
      IF ( NZ.GT.NZMAX ) GOTO 540
      if(iop.eq.1)write(50,924) ETA
!
      RETURN
 540  write(50,936) NZMAX
 850  ERR = .TRUE.
      RETURN
!
 900  FORMAT(56H0SAFE DISTANCE (1.20*(AP**(1/3)+AT**(1/3)) + 4.0)FERMI=  
     1 ,F6.2,6H FERMI,//44H WARNING  --  BOMBARDING ENERGY TOO HIGH FOR
     218H HEAD-ON COLLISION,/34H CRITICAL SCATTERING ANGLE THETA =
     3F6.2,21H DEGREES IN CM SYSTEM/)
 902  FORMAT(10H0XI MATRIX)
 904  FORMAT(///)
 906  FORMAT(6X,I14,10I11)
 908  FORMAT(1H05X3HN =I2,11F11.4)
 910  FORMAT(1H1)
 912  FORMAT(/18H0PSI MATRIX FOR  EI1)
 914  FORMAT(45H0TOTAL NUMBER OF MAGNETIC SUBSTATES, ISMAX = I3)
 916  FORMAT(28H0 ERROR ISMAX EXCEEDS ICATMX,5X,9H(ICATMX =I4,1H))
 918  FORMAT(17H0SSTART ARRAY    ,20I5/17X20I5)
 920  FORMAT(17H0SSTOP  ARRAY    ,20I5/17X20I5,//)
 922  FORMAT(36H0NUMBER OF ELEMENTS IN ZETA-ARRAY = I5)
 924  FORMAT(7H0ETA = F6.2)
 936  FORMAT(57H0ERROR  -  NUMBER OF ELEMENTS IN ZETA ARRAY EXCEEDS NZMA
     1X,5X,8H(NZMAX =I6,1H))
 938  FORMAT(/18H0PSI MATRIX FOR  MI1)
 940  FORMAT(1H05X3HN =I2,11E11.3)
 942  FORMAT(//37H0INITIAL VELOCITY OF PROJECTILE V/C =F6.3,
     1/56H DISTANCE OF CLOSED APPROACH IN HEAD-ON COLLISION 2*A =,
     2F8.2,6H FERMI)
      END
      SUBROUTINE PREP2
!
!     THIS ROUTINE COMPUTES RANGE AND STEP WIDTH OF INTEGRATION
!
      INTEGER OUXI,OUPSI
      LOGICAL ERR
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON/BL19/ERR
      COMMON/BL21/XIMAX
      COMMON/BL22/THETA
      COMMON/BL25/EPS,EROOT
      COMMON/BL32/NMAX,NDIM
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL39/UP,DW,ISTEP,D2W
      COMMON/BL41/XI(25,25)
      COMMON/BL42/TCMDG(25),ZLBDG(25),R3(25),R4(25),EPP(25),
     1ETP(25)
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL54/DISTA
	common/output/iop
!
!     TRANSITION TO CM COORDINATE SYSTEM IF SCATTERING ANGLE IS GIVEN
!     IN LABORATORY SYSTEM
      IF(TLBDG.EQ.0.0.AND.THETA.NE.0.0) GOTO 100
      CALL CMLAB(A1,A2,EP,EN,NMAX,TLBDG,TCMDG,ZLBDG,R3,R4,EPP,ETP)
      IF(ERR) GOTO 850
      THETA=TCMDG(NCM)
      if(iop.eq.1)write(50,902) THETA
!
!     RANGE AND STEP WIDTH OF INTEGRATION
 100  TRAD=THETA/57.295779
      STR = SIN(TRAD/2.0)
      EPS = 1.0/STR
      EROOT = SQRT(EPS*EPS-1.)
      CLOSE = DISTA*(1.+EPS)*10.0
      UP=ALOG(1.0/(EPS*SQRT(ACCUR)))
!     DETERMINATION OF THE LARGEST XI-VALUE USED IN THE CALCULATION
      XIM = 0.0
      DO 200 N = 1,NMAX
      DO 150 M = 1,NMAX
      IF(XI(N,M).GT.XIMAX)GOTO 150
      IF(XI(N,M).LE.XIM)GOTO 150
      XIM = XI(N,M)
 150  CONTINUE
 200  CONTINUE
      if(iop.eq.1)write(50,900)XIM
      DW=40.0*(ACCUR**0.2)/(10.0+48.0*XIM+16.0*XIM*EPS)
      ISTEP=UP/(DW*8.)+1.
      ISTEP=ISTEP*8
      DW=UP/(FLOAT(ISTEP)-0.25)
      UP=DW*FLOAT(ISTEP)
      if(iop.eq.1)write(50,904)EPS,CLOSE,UP,ISTEP
      D2W = DW + DW
      if(iop.eq.1)write(50,906)D2W
 850  RETURN
!
 900  FORMAT(7H0XIM = F11.4)
 902  FORMAT(29H0CM SCATTERING ANGLE USED IS F7.2,8H DEGREES)
 904  FORMAT(7H0EPS = F7.3,/
     133H0DISTANCE OF CLOSEST APPROACH IS F8.2,6H FERMI/
     228H0RANGE OF INTEGRATION, UP = F6.2 /
     336H0ESTIMATED NUMBER OF STEPS, ISTEP = I4)
 906  FORMAT(27H0INITIAL STEP WIDTH, D2W = F8.5)
      END
      SUBROUTINE PREP3(K)
!
!     THIS ROUTINE IS CALLED DURING THE INTEGRATION OF THE AMPLITUDES
!     IT DETERMINES THE RANGE OF DO-LOOPS FOR TARGET AND PROJECTILE
!     EXCITATION (K=1,2)
!
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL12/LMX,IR1,IR2,N1,N2
      COMMON/BL32/NMAX,NDIM
!
      LMX = LMAX(K)
      IR1 = IRSTA(K)
      IR2 = IRSTO(K)
      IF(K.EQ.2)GOTO 100
      N1 = 1
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      RETURN
 100  N1 = NSTART(IP)
      N2 = NMAX
      RETURN
      END
      SUBROUTINE Q(W)
!
!     THIS ROUTINE COMPUTES Q-FUNCTIONS
!
      IMPLICIT COMPLEX (A)
      REAL ACCUR
      COMPLEX CI,EX,QLM(12,7),DEN7,DEN8,DEN9,DEN10,DEN11,DEN12
      COMPLEX CQU1,CQU2,CQU3,CQU4,CQU5,CQU6,CQU7,CQU8,CQU9,CQU10,CQU11,
     1CQU12
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL4/MAGEXC
      COMMON/BL13/CQU1(7,25,25),CQU2(7,25,25),CQU3(7,25,25)
      COMMON/BL14/CQU4(7,25,25),CQU5(7,25,25),CQU6(7,25,25)
      COMMON/BL15/CQU7(7,25,25),CQU8(7,25,25),CQU9(7,25,25)
      COMMON/BL16/CQU10(7,25,25),CQU11(7,25,25),
     1CQU12(7,25,25)
      COMMON/BL25/EPS,EROOT
      COMMON/BL32/NMAX,NDIM
      COMMON/BL41/XI(25,25)
      DATA CI/(0.0,1.0)/
!
!      VARIABLES NEEDED FOR THE CALCULATION OF QLM(LAM,MY)
      EW=EXP(W)
      COSHY=0.5*(EW+1.0/EW)
      SINHY=0.5*(EW-1.0/EW)
      DEN=EPS*COSHY+1.0
      POL = 1.0-ZPOL/DEN
!     POL ACCOUNTS FOR THE VIRTUAL EXCITATION OF THE DIPOLE GIANT RESONA
      DEN1=DEN*DEN
      DEN2=DEN1*DEN1
      DEN3=DEN2*DEN1
      DEN4=DEN2*DEN2
      DEN5=DEN4*DEN1
      DEN6=DEN3*DEN3
      SH1=EROOT*SINHY
      SH2=SH1*SH1
      SH3=SH2*SH1
      SH4=SH2*SH2
      SH5=SH2*SH3
      SH6=SH2*SH4
      CH1=COSHY+EPS
      CH2=CH1*CH1
      CH4=CH2*CH2
      IF(MAGEXC.EQ.0) GOTO 100
!     QUANTITIES NEEDED ONLY FOR MAGNETIC EXCITATIONS
      A = COSHY + EPS + CI*EROOT*SINHY
      B = EPS*COSHY + 1.
      B2 = B*B
      A2 = A*A
      B4 = B2*B2
      A4 = A2*A2
      A2B2 = A2*B2
      B6 = B4*B2
      A6 = A4*A2
      A2B4 = A2B2 * B2
      A4B2 = A4 * B2
      B8 = B6 * B2
      A8 = A6 * A2
      A2B6 = A2B4 * B2
      A4B4 = A4B2 * B2
      A6B2 = A6 * B2
      B10 = B8 * B2
      A10 = A8 * A2
      A2B8 = A2B6 * B2
      A4B6 = A4B4 * B2
      A6B4 = A6B2 * B2
      A8B2 = A8 * B2
      A1B2 = A * B2
      DEN7 = B2
      DEN8 = DEN7 * A1B2
      DEN9 = DEN8 * A1B2
      DEN10 = DEN9 * A1B2
      DEN11 = DEN10 * A1B2
      DEN12 = DEN11 * A1B2
!
!     COMPUTE FUNCTIONS QLM(LAM,MY)
 100  DO 300 I1=1,LAMMAX
      LAM = LAMDA(I1)
      GOTO(110,120,130,140,150,160,210,220,230,240,250,260),LAM
 110  QLM(1,1)= 0.5*CH1/DEN1
      QLM(1,2)=-0.35355339*CI*SH1/DEN1
      GOTO 300
 120  QLM(2,1)= 0.75*(2.0*CH2-SH2)/DEN2 * POL
      QLM(2,2)=-1.83711730*CI*CH1*SH1/DEN2 * POL
      QLM(2,3)=-0.91855865*SH2/DEN2 * POL
      GOTO 300
 130  QLM(3,1)= 1.875*CH1*(2.0*CH2-3.0*SH2)/DEN3
      QLM(3,2)=-1.62379763*CI*(4.0*CH2-SH2)*SH1/DEN3
      QLM(3,3)=-5.13489890*CH1*SH2/DEN3
      QLM(3,4)= 2.09631373*CI*SH3/DEN3
      GOTO 300
 140  QLM(4,1)= 1.09375000*(8.0*CH4-24.0*CH2*SH2+3.0*SH4)/DEN4
      QLM(4,2)=-4.89139867*CI*CH1*(4.0*CH2-3.0*SH2)*SH1/DEN4
      QLM(4,3)=-3.45874113*(6.0*CH2-SH2)*SH2/DEN4
      QLM(4,4)=12.9414244 *CI*CH1*SH3/DEN4
      QLM(4,5)= 4.57548440*SH4/DEN4
      GOTO 300
 150  QLM(5,1)=1.230468*CH1*(-14.*CH2*(9.*SH2+DEN1)+30.*DEN2)/DEN5
      QLM(5,2)=-1.347911*CI*SH1*(35.*CH2*(-3.*SH2+DEN1)+5.*DEN2)/DEN5
      QLM(5,3)=-35.662372*SH2*CH1*(-3.*SH2+2.*DEN1)/DEN5
      QLM(5,4)=7.279552*CI*SH3*(9.*CH2-DEN1)/DEN5
      QLM(5,5)=30.884521*SH4*CH1/DEN5
      QLM(5,6)=-9.766543*CI*SH5/DEN5
      GOTO 300
 160  QLM(6,1)=2.707031*(21.*CH2*(-CH2*(11.*SH2+4.*DEN1)+5.*DEN2)-
     1 5.*DEN3)/DEN6
      QLM(6,2)=-17.543567*CI*SH1*CH1*(3.*CH2*(-11.*SH2+DEN1)+5.*DEN2)/
     1 DEN6
      QLM(6,3)=-13.869408*SH2*(3.*CH2*(-11.*SH2+5.*DEN1)+DEN2)/DEN6
      QLM(6,4)=-27.738815*CI*SH3*CH1*(-11.*SH2+8.*DEN1)/DEN6
      QLM(6,5)=15.193177*SH4*(11.*CH2-DEN1)/DEN6
      QLM(6,6)=-71.262308*CI*SH5*CH1/DEN6
      QLM(6,7)=-20.571656*SH6/DEN6
      GOTO 300
 210  QLM(7,1) = (0.,0.)
      QLM(7,2) = -0.35355339*EROOT/DEN7
      GOTO 300
 220  AFAC = EROOT/DEN8
      QLM(8,1)=(0.,0.)
      QLM(8,2)=-0.45927933*AFAC*(B2+A2)
      QLM(8,3)=-0.45927933*AFAC*(B2-A2)
      GOTO 300
 230  AFAC = EROOT/DEN9
      QLM(9,1)=(0.,0.)
      QLM(9,2)=-0.13531647*AFAC*(5.*B4+6.*A2B2+5.*A4)
      QLM(9,3)=-0.85581650*AFAC*(B4-A4)
      QLM(9,4)=-0.52407843*AFAC*(B2-A2)**2
      GOTO 300
 240  AFAC = EROOT/DEN10
      QLM(10,1)=(0.,0.)
      QLM(10,2)=-.15285621*AFAC*(7.*B6+9.*A2B4+9.*A4B2+7.*A6)
      QLM(10,3)=-.21617132*AFAC*(7.*B6+3.*A2B4-3.*A4B2-7.*A6)
      QLM(10,4)=-1.21325855*AFAC*(B6-A2B4-A4B2+A6)
      QLM(10,5)=-.57193557*AFAC*(B2-A2)**3
      GOTO 300
 250  AFAC = EROOT/DEN11
      QLM(11,1)=(0.,0.)
      QLM(11,2)=-0.08424444*AFAC*(21.*B8+28.*A2B6+30.*A4B4+28.*A6B2
     1+21.*A8)
      QLM(11,3)=-0.89155931*AFAC*(3.*B8+2.*A2B6-2.*A6B2-3.*A8)
      QLM(11,4)=-0.27298317*AFAC*(9.*B8-4.*A2B6-10.*A4B4-4.*A6B2+9.*A8)
      QLM(11,5)=-1.54422603*AFAC*(B8-2.*A2B6+2.*A6B2-A8)
      QLM(11,6)=-0.61040893*AFAC*(B2-A2)**4
      GOTO 300
 260  AFAC = EROOT/DEN12
      QLM(12,1)=(0.,0.)
      QLM(12,2)=-0.09137275*AFAC*(33.*B10+45.*A2B8+50.*A4B6+50.*A6B4
     1+45.*A8B2+33.*A10)
      QLM(12,3)=-0.14447300*AFAC*(33.*B10+27.*A2B8+10.*A4B6-10.*A6B4
     1-27.*A8B2-33.*A10)
      QLM(12,4)=-0.43341900*AFAC*(11.*B10-A2B8-10.*A4B6-10.*A6B4-A8B2
     1+11.*A10)
      QLM(12,5)=-0.31652448*AFAC*(11.*B10-15.*A2B8-10.*A4B6+10.*A6B4
     1+15.*A8B2-11.*A10)
      QLM(12,6)=-1.85578928*AFAC*(B10-3.*A2B8+2.*A4B6+2.*A6B4-3.*A8B2
     1+A10)
      QLM(12,7)=-0.64286427*AFAC*(B2-A2)**5
 300  CONTINUE
!
!     MULTIPLY QLM(LAM,MY) WITH THE KINETIC EXPONENTIAL-FACTOR
      RALFA=EPS*SINHY+W
      DO 930 I1=1,LAMMAX
      LAM = LAMDA(I1)
      LA = LAM
      IF(LAM.GT.6) LAM=LAM-6
      MYMAX = LAM + 1
      DO 920 N=1,NMAX
      LD = LDNUM(LA,N)
      IF(LD.EQ.0) GOTO 920
      DO 910 I2=1,LD
      M = LEAD(N,I2,LA)
      IF(N.EQ.M)GOTO 610
      X = XI(N,M)
      EX = COS(X*RALFA) + CI*SIN(X*RALFA)
      DO 600 MY=1,MYMAX
      GOTO(410,420,430,440,450,460,510,520,530,540,550,560),LA
 410  CQU1(MY,N,M) = QLM(LA,MY)*EX
      CQU1(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 420  CQU2(MY,N,M) = QLM(LA,MY)*EX
      CQU2(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 430  CQU3(MY,N,M) = QLM(LA,MY)*EX
      CQU3(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 440  CQU4(MY,N,M) = QLM(LA,MY)*EX
      CQU4(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 450  CQU5(MY,N,M) = QLM(LA,MY)*EX
      CQU5(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 460  CQU6(MY,N,M) = QLM(LA,MY)*EX
      CQU6(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 510  CQU7(MY,N,M) = QLM(LA,MY)*EX
      CQU7(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 520  CQU8(MY,N,M) = QLM(LA,MY)*EX
      CQU8(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 530  CQU9(MY,N,M) = QLM(LA,MY)*EX
      CQU9(MY,M,N) = QLM(LA,MY)/EX
      GOTO 600
 540  CQU10(MY,N,M)= QLM(LA,MY)*EX
      CQU10(MY,M,N)= QLM(LA,MY)/EX
      GOTO 600
 550  CQU11(MY,N,M)= QLM(LA,MY)*EX
      CQU11(MY,M,N)= QLM(LA,MY)/EX
      GOTO 600
 560  CQU12(MY,N,M)= QLM(LA,MY)*EX
      CQU12(MY,M,N)= QLM(LA,MY)/EX
 600  CONTINUE
      GOTO 910
 610  DO 900 MY=1,MYMAX
      GOTO(710,720,730,740,750,760,810,820,830,840,850,860),LA
 710  CQU1(MY,N,M) = QLM(LA,MY)
      GOTO 900
 720  CQU2(MY,N,M) = QLM(LA,MY)
      GOTO 900
 730  CQU3(MY,N,M) = QLM(LA,MY)
      GOTO 900
 740  CQU4(MY,N,M) = QLM(LA,MY)
      GOTO 900
 750  CQU5(MY,N,M) = QLM(LA,MY)
      GOTO 900
 760  CQU6(MY,N,M) = QLM(LA,MY)
      GOTO 900
 810  CQU7(MY,N,M) = QLM(LA,MY)
      GOTO 900
 820  CQU8(MY,N,M) = QLM(LA,MY)
      GOTO 900
 830  CQU9(MY,N,M) = QLM(LA,MY)
      GOTO 900
 840  CQU10(MY,N,M)= QLM(LA,MY)
      GOTO 900
 850  CQU11(MY,N,M)= QLM(LA,MY)
      GOTO 900
 860  CQU12(MY,N,M)= QLM(LA,MY)
 900  CONTINUE
 910  CONTINUE
 920  CONTINUE
 930  CONTINUE
      RETURN
      END
      SUBROUTINE ROTATE(RHONEW,RHOOLD,ALPHA,BETA,GAMMA)
!
!     THIS ROUTINE TRANSFORMS THE STATISTICAL TENSORS FROM
!     ONE COORDINATE SYSTEM TO ANONTHER ONE GENERATED BY A
!     ROTATION WITH THE EULERIAN ANGLES ALPHA, BETA, GAMMA
!
      COMPLEX CI,RHOOLD,RHONEW,TE
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL32/NMAX,NDIM
      DIMENSION RHOOLD(25,3,5),RHONEW(25,3,5)
      DATA CI/(0.0,1.0)/
!
      ALPHAR = ALPHA/57.295779
      GAMMAR = GAMMA/57.295779
      DO 590 K=1,IEXNUM
      N1 = 2
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IF(K.EQ.1)GOTO 510
      N1 = NSTART(IP) + 1
      N2 = NMAX
 510  DO 580 N=N1,N2
      KA = 0
      KAMAX = 2.02*SPIN(N)
      IF(KAMAX.GT.4) KAMAX=4
      KASTOP = KAMAX + 1
      DO 570 KAI=1,KASTOP,2
!     KAI IS INDEX COUNTER ONLY
      DJ = KA
      KAINDX = KA/2 + 1
      KAPPA = KA
      KAPSTP = KA + 1
      DO 560 KAPPI=1,KAPSTP
!     KAPPI IS INDEX COUNTER ONLY
      DMP = KAPPA
      KAPPIN = KAPPA + 1
      TE = (0.,0.)
!     SUMMATION OVER INDICES .GE. 0 IN EQUATION (I.4.4)
      KPR = 0
 520  DM = KPR
      KPRI = KPR + 1
      TE = TE+RHOOLD(N,KAINDX,KPRI)*(COS(KPR*ALPHAR) -
     1CI*SIN(KPR*ALPHAR))*DJMM(BETA,DJ,DM,DMP)
      KPR = KPR + 1
      IF(KPR.LE.KA)GOTO 520
      IF(KA.EQ.0)GOTO 550
!     SUMMATION OVER NEGATIVE INDICES IN EQUATION (I.4.4)
      KPR = 1
 540  DM = -KPR
      KPRI = KPR + 1
      TE = TE+(-1)**KPR*CONJG(RHOOLD(N,KAINDX,KPRI))*(COS(-KPR*
     1ALPHAR)-CI*SIN(-KPR*ALPHAR))*DJMM(BETA,DJ,DM,DMP)
      KPR = KPR + 1
      IF(KPR.LE.KA)GOTO 540
 550  RHONEW(N,KAINDX,KAPPIN)=TE*(COS(KAPPA*GAMMAR)-CI*
     1SIN(KAPPA*GAMMAR))
      KAPPA = KAPPA - 1
 560  CONTINUE
      KA = KA + 2
 570  CONTINUE
 580  CONTINUE
 590  CONTINUE
      RETURN
      END
      SUBROUTINE SIGM
!
!     THIS ROUTINE COMPUTES THE DIFFERENTIAL CROSS SECTIONS AND PERFORMS
!     THE INTEGRATION OVER SCATTERING ANGLES
!
      LOGICAL ERR
      INTEGER OURHOB,OURHOC,OURHOX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON/BL11/INTEND
      COMMON/BL19/ERR
      COMMON/BL21/XIMAX
      COMMON/BL22/THETA
      COMMON/BL25/EPS,EROOT
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL41/XI(25,25)
      COMMON/BL42/TCMDG(25),ZLBDG(25),R3(25),R4(25),EPP(25),
     1ETP(25)
      COMMON/BL45/DTHETR,DTLBR
      COMMON/BL46/DSIG(25),DSIGLB(25),RU(25)
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL51/SIGTOT(25)
      COMMON/BL53/P(25)
      COMMON/BL54/DISTA
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop
!
!     COMPUTATION AND PRINT-OUT OF THE DIFFERENTIAL CROSS-SECTIONS
      IF(TLBDG.NE.0.)GOTO 110
!     HEADING FOR CM CROSS SECTIONS
      if(iop.eq.1)write(50,902) THETA
      if(iop.eq.1)write(50,904)
      GOTO 120
!     HEADING FOR LAB CROSS SECTIONS
 110  if(iop.eq.1)write(50,906) TLBDG
      if(iop.eq.1)write(50,908)
 120  DO 190 I=1,NGMAX
      if(iop.eq.1)write(50,910) I
      N1 = NSTART(I)
      N2 = NSTOP(I)
      DO 180 N=N1,N2
      RU(N)=0.25*SQRT(EP/(EP-(1.0+A1/A2)*EN(N)))*DISTA**2*EPS**4
      DSIG(N) = RU(N)*P(N)
      IF(TLBDG.NE.0.)GOTO 160
      if(iop.eq.1)write(50,912)N,P(N),DSIG(N)
      GOTO 180
 160  DSIGLB(N) = DSIG(N)*R3(N)
      if(iop.eq.1)write(50,916)N,TCMDG(N),P(N),DSIGLB(N)
	1         ,EPP(N),ETP(N),ZLBDG(N),R4(N)
 180  CONTINUE
 190  CONTINUE
!
!     PRINT-OUT OF THE STATISTICAL TENSORS
      IF(OURHOB.EQ.0)GOTO 250
      write(50,920)
      CALL TENS2(1)
 250  IF(OURHOC.EQ.0)GOTO 270
      if(iop.eq.1)write(50,926)
      CALL TENS2(2)
 270  IF(OURHOX.EQ.0)GOTO 310
      write(50,928)
      CALL TENS2(5)
      write(50,930) ALPHA,BETA,GAMMA
!
!     RETURNS TO MAIN PROGRAM IF NO INTEGRATION OVER SCATTERING ANGLE
!     IS PERFORMED
 310  IF(SIMP.EQ.0.0) RETURN
!     INTEGRATION OVER SCATTERING ANGLE
!
      IF( TLBDG.NE.0.0) GOTO 380
!     TOTAL CROSS SECTIONS FROM CM DIFFERENTIAL CROSS SECTIONS
      DO 330 N=2,NMAX
      SIGTOT(N)=2.0*3.1415926*DTHETR/3.0*SIMP*DSIG(N)*SIN(THETA/57.29577
     19) + SIGTOT(N)
 330  CONTINUE
!     TOTAL STATISTICAL TENSORS
      IF(OURHOC.EQ.0)GOTO 350
      CALL TENS2(3)
 350  THETA = THETA - DTHETA
      IF(THETA.LT.0.5*DTHETA)GOTO 500
      GOTO 440
!     TOTAL CROSS SECTIONS FROM LABORATORY DIFF CROSS SECTIONS
 380  DO 390 N=1,NMAX
      SIGTOT(N)=2.*3.1415926*DTLBR/3.*SIMP*DSIGLB(N)*
     1SIN(TLBDG/57.295779) + SIGTOT(N)
 390  CONTINUE
!     TOTAL STATISTICAL TENSORS
      IF(OURHOC.EQ.0)GOTO 410
      CALL TENS2(6)
 410  TLBDG = TLBDG-DTLBDG
      IF(TLBDG.LT.THI-0.01)GOTO 500
      IF(TLBDG.GT.THI+0.0001)GOTO 440
      SIMP = 1.0
      GOTO 570
!     ADJUST THE VARIABLE SIMP
 440  IF (SIMP.LE.2.001) GOTO 450
      IF(SIMP.LE.3.001) GOTO 570
      SIMP =2.0
      GOTO 570
 450  SIMP =4.0
      GOTO 570
!
!     PRINT-OUT OF TOTAL CROSS SECTIONS AND TOTAL STATISTICAL TENSORS
 500  CONTINUE
      IF(TLBDG.NE.0.0) GOTO 510
      write(50,938)
      GOTO 520
 510  write(50,940)TLI,THI
 520  write(50,942)
      NMIN=2
      IF(TLBDG.NE.0.0.AND.THI.GT.0.01) NMIN=1
      DO 530 N=NMIN,NMAX
 530  write(50,944) N,SIGTOT(N)
      INTEND = 1
      IF(OURHOC.EQ.0)GOTO 560
      write(50,946)
      CALL TENS2(4)
 560  IF(OURHOX.EQ.0)GOTO 570
      write(50,947)
      CALL TENS2(12)
 570  RETURN
!
 902  FORMAT(52H0SCATTERING ANGLE IN CENTER OF MASS SYSTEM  THETA = F7.2
     1,8H DEGREES)
 904  FORMAT(1H0,12H LEVEL INDEX10X10HEXCITATION11X16HCM CROSS SECTION/
     122X13HPROBABILITIES9X15HBARNS/STERADIAN//7X1HN18X4HP(N)18X
     27HDSIG(N))
 906  FORMAT(48H0SCATTERING ANGLE IN LABORATORY SYSTEM  TLBDG = F7.2,
     1 8H DEGREES)
 908  FORMAT(6H0LEVEL4X10HSCATTERING8X10HEXCITATION8X9HLAB CROSS9X
     19HENERGY OF9X9HERERGY OF9X10HLAB RECOIL8X11HSOLID ANGLE/6H INDEX
     24X8HANGLE-CM10X13HPROBABILITIES5X7HSECTION11X9HSCATTERED9X6HRECOIL
     33HING9X5HANGLE13X9HRATIO FOR/10X7HDEGREES29X15HBARNS/STERADIAN
     43X14HPROJECTILE,MEV4X10HTARGET,MEV8X,7HDEGREES11X6HRECOIL//3X1HN6X
     58HTCMDG(N)10X4HP(N)14X9HDSIGLB(N)9X6HEPP(N)12X6HETP(N)12X
     68HZLBDG(N)10X5HR4(N))
 910  FORMAT(6H0GROUPI3,/)
 912  FORMAT (I8,6X,E19.4,5X,E19.4)
 916  FORMAT(1XI3,5XF7.2,7XE14.4,4XE14.4,8XF9.4,9XF9.4,9XF9.4,7XF9.4)
 920  FORMAT(1H0,9X40HTHE STATISTICAL TENSORS RHOB(N,KA,KAPPA))
 926  FORMAT(1H0,9X40HTHE STATISTICAL TENSORS RHOC(N,KA,KAPPA))
 928  FORMAT(1H0,9X40HTHE STATISTICAL TENSORS RHOX(N,KA,KAPPA))
 930  FORMAT(31H0EULERIAN ANGLES USED   ALPHA = F7.2,3X,7HBETA = F7.2,
     13X,8HGAMMA = F7.2)
 938  FORMAT(1H1,16X,29HTOTAL CROSS SECTIONS IN BARNS)
 940  FORMAT(56H1TOTAL LABORATORY CROSS SECTIONS IN RING COUNTER BETWEEN
     1 F7.2,13H DEGREES AND F7.2, 8H DEGREES,11H (IN BARNS))
 942  FORMAT(1H0,6X1HN18X9HSIGTOT(N) )
 944  FORMAT(5XI3,11XE19.4)
 946  FORMAT(44H1TOTAL STATISTICAL TENSORS RHOCT(N,KA,KAPPA)//)
 947  FORMAT(44H1TOTAL STATISTICAL TENSORS RHOXT(N,KA,KAPPA)//)
      END
      SUBROUTINE START
!
!     THIS ROUTINE STARTS EXECUTION OF PROGRAM
!
      LOGICAL ERR
      INTEGER OUAMP,OUPROW,OUXI,OUPSI
      INTEGER OURHOB,OURHOC,OURHOX
      COMPLEX RHOCT
      REAL MEM
      COMMON /BL1/LAMDA(12),LEAD(25,25,12),LDNUM(12,25),LAMMAX
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL10/IPAR(25),IFAC(25)
      COMMON/BL19/ERR
      COMMON/BL20/MEM(25,25,12),MULT(25,25,12)
      COMMON/BL21/XIMAX
      COMMON/BL22/THETA
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL30/RHOCT(25,3,5)
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL33/NTIME
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL45/DTHETR,DTLBR
      COMMON/BL48/NANGLE,THI,TLI
      COMMON/BL49/OUAMP,OUPROW,INTERV,INTIN
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      COMMON/BL51/SIGTOT(25)
      COMMON/BL55/DTHETA,DTLBDG
	common/output/iop
!
      INTERV = INTIN
      THETA = THI
      TLBDG = TLI
!
!     CHECK AND SYMMETRIZATION OF MEM-MATRIX BY SUBROUTINE MAT
      CALL MAT
      IF(ERR) RETURN
      IF (NGMAX.NE.1) GOTO 110
!
!     CONSTRUCTION OF GROUPS FOR NMAX .GT. 11 BY THE PROGRAM
      NGMAX = NMAX/11
      NGMAX = NGMAX + 1
      IF(MOD(NMAX,11).EQ.0) NGMAX=NMAX/11
      NSTA = 1
      NSTO = 11
      DO 100 I=1,NGMAX
      IEXCIT(I) = IEXCIT(1)
      EMMAX(I) = EMMAX1
      NSTART(I) = NSTA
      NSTOP(I) = NSTO
      IF(I.EQ.NGMAX) NSTOP(I)=NMAX
      NSTA = NSTA+11
      NSTO = NSTO+11
 100  CONTINUE
      GOTO 180
!
!     SYMMETRIZATION OF MASTER - MATRIX
 110  DO 170 I1 = 1,NGMAX
      DO 170 I2 = I1,NGMAX
      MASTER(I2,I1) = MASTER(I1,I2)
 170  CONTINUE
!
!     COMPUTATION OF IFAC-ARRAY
 180  DO 220 K=1,IEXNUM
      IF(K.EQ.2)GOTO 190
      N1 = 1
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2 = NSTART(IP) - 1
      GOTO 200
 190  N1 = NSTART(IP)
      N2 = NMAX
 200  DO 210 N=N1,N2
      ISPIN = SPIN(N) + 0.0001
      IDPAR = 0
      IF(IPAR(N).NE.IPAR(N1)) IDPAR=1
      IFAC(N) = (-1)**(IDPAR-ISPIN)
 210  CONTINUE
 220  CONTINUE
      IF (NCM .GT. NMAX) NCM = NMAX
!
!     PRINT-OUT OF INPUT DATA
      if(iop.eq.1)write(50,900)
      if(iop.eq.1)write(50,902) ZP,A1,EP
      if(iop.eq.1)write(50,904) DIPOL
      IF(TLI.EQ.0.0.AND.THI.EQ.0.0) GOTO 330
!     STATEMENT 330 PREPARES THE COMPUTATION OF TOTAL CROSS SECTIONS
      IF(TLI.NE.0.0.AND.THI.NE.0.0) GOTO 350
!     STATEMENT 350 PREPARES THE COMPUTATION OF CROSS-SECTIONS FOR A
!     RING-COUNTER
      SIMP = 0.0
      NANGLE=0
      THETA = THI
      TLBDG = TLI
      IF(TLBDG.NE.0.)GOTO 240
      if(iop.eq.1)write(50,906) THETA
      GOTO 250
 240  if(iop.eq.1)write(50,908) TLBDG
 250  if(iop.eq.1)write(50,910) ZT,A2
      if(iop.eq.1)write(50,912) NGMAX
      if(iop.eq.1)write(50,914)
      DO 260 I=1,NGMAX
      N1 = NSTART(I)
      N2 = NSTOP(I)
      if(iop.eq.1)write(50,916) I, (N,N=N1,N2)
      if(iop.eq.1)write(50,918)(EN(N),N=N1,N2)
      if(iop.eq.1)write(50,920)(SPIN(N),N=N1,N2)
      if(iop.eq.1)write(50,922) (IPAR(N),N=N1,N2)
 260  CONTINUE
      IF(NGMAX.EQ.1) GOTO 280
!     PRINTOUT OF MASTER - MATRIX
      if(iop.eq.1)write(50,924)
      if(iop.eq.1)write(50,926) ( I, I=1,NGMAX)
      DO 270 N=1,NGMAX
      if(iop.eq.1)write(50,928) N, ( MASTER(N,I), I = 1,NGMAX)
 270  CONTINUE
 280  CONTINUE
!     PRINT-OUT OF THE MATRIX ELEMENTS
      if(iop.eq.1)write(50,930)
      if(iop.eq.1)write(50,960)
      DO 320 I5=1,LAMMAX
      LAM = LAMDA(I5)
      IF(LAM.GT.6)GOTO 282
      if(iop.eq.1)write(50,932) LAM
      GOTO 283
 282  LA = LAM - 6
      if(iop.eq.1)write(50,962) LA
 283  NN = 1
      IF(NMAX.GT.11) NN=NGMAX
      DO 310 I=1,NN
      M1 = NSTART(I)
      M2 = NSTOP(I)
      IF(NMAX.GT.11)GOTO 285
      M1 = 1
      M2 = NMAX
 285  if(iop.eq.1)write(50,936) (M,M=M1,M2)
      DO 290 N=1,NMAX
      K = 0
      DO 286 M=M1,M2
      RMEM = MEM(N,M,LAM)
      IF(RMEM.NE.0..AND.ABS(RMEM).LT.0.001) K=1
 286  CONTINUE
      IF(K.EQ.1)GOTO 288
      if(iop.eq.1)write(50,938) N,(MEM(N,M,LAM),M=M1,M2)
      GOTO 290
 288  if(iop.eq.1)write(50,964) N,(MEM(N,M,LAM),M=M1,M2)
 290  CONTINUE
      if(iop.eq.1)write(50,934)
 310  CONTINUE
 320  CONTINUE
      if(iop.eq.1)write(50,940)
      if(iop.eq.1)write(50,942)NMAX,INTERV,NCM,XIMAX,ACCUR,NTIME
      if(iop.eq.1)write(50,944) (I,I=1,NGMAX)
      if(iop.eq.1)write(50,946) (EMMAX(I),I=1,NGMAX)
      if(iop.eq.1)write(50,948) (IEXCIT(I),I=1,NGMAX)
      if(iop.eq.1)write(50,950)
      if(iop.eq.1)write(50,952) OUXI,OUPSI,OUAMP,OUPROW,OURHOB,OURHOC,OURHOX
      GOTO 400
!
!     PREPARE THE COMPUTATION OF TOTAL CROSS SECTIONS
 330  if(iop.eq.1)write(50,954)
      RANGLE = 180.0/DTHETA
      NANGLE = RANGLE
      IF(ABS(RANGLE-NANGLE).GT.1.E-6) NANGLE=NANGLE+1
      IF(MOD(NANGLE,2).EQ.0)GOTO 340
      NANGLE = NANGLE + 1
 340  DTHETA = 180.0/FLOAT(NANGLE)
      if(iop.eq.1)write(50,966) DTHETA
      DTHETR = DTHETA/57.295779
      NANGLE = NANGLE - 1
      THETA = 180.0 - DTHETA
      SIMP = 4.0
      GOTO 380
!
!     PREPARE THE COMPUTATION OF CROSS-SECTIONS FOR A
!     RING-COUNTER
 350  IF(TLI.EQ.THI) GOTO 410
      IF(TLI.GT.THI)GOTO 355
      T = TLBDG
      TLBDG = THETA
      THETA = T
      T = TLI
      TLI = THI
      THI = T
 355  if(iop.eq.1)write(50,956)TLI,THI
      DELTHE = TLI - THI
      DTLBDG = DTHETA
      IF(IDN25.NE.0)GOTO 356
      IF(DELTHE.LE.20.)GOTO 360
 356  RANGLE = DELTHE/DTLBDG
      NANGLE = RANGLE
      IF(ABS(RANGLE-NANGLE).GT.1.E-6) NANGLE=NANGLE+1
      IF(MOD(NANGLE,2).NE.0) NANGLE=NANGLE+1
      DTLBDG = DELTHE/FLOAT(NANGLE)
      NANGLE = NANGLE + 1
      if(iop.eq.1)write(50,966) DTLBDG
      DTLBR = DTLBDG/57.295779
      IF(TLI.EQ.180.)GOTO 358
      SIMP =1.0
      GOTO 380
 358  TLBDG = TLI - DTLBDG
      SIMP = 4.0
      GOTO 380
 360  IF(DELTHE.LE.10.)GOTO 370
      DTLBDG = 0.6*DELTHE
      DTLBR = DTLBDG/57.295779
      TLBDG = TLI-0.2*DELTHE
      NANGLE=2
      SIMP=2.5
      GOTO 380
 370  TLBDG = TLI-0.5*DELTHE
      DTLBDG = DELTHE
      DTLBR = DTLBDG/57.295779
      NANGLE=1
      SIMP=3.0
!
!     INITIALIZE SIGTOT(N), RHOCT(N,K,KAPPA)
 380  DO 390 N=1,NMAX
      SIGTOT(N) = 0.0
      DO 390 L=1,5
      DO 390 K=1,3
      RHOCT(N,K,L) = 0.0
 390  CONTINUE
      GOTO 250
 400  RETURN
!
!     ERROR EXIT
 410  write(50,958)
      ERR = .TRUE.
      RETURN
!
 900  FORMAT(12H1COULEX 1978,/28H MULTIPLE COULOMB EXCITATION,
     18H PROGRAM,2X,26HFOR  E1 - E6  AND  M1 - M6//)
 902  FORMAT(32H0PROJECTILE CHARGE NUMBER  ZP = F6.2,14H,  MASS  A1 =  
     1F8.3,23HAMU,  LAB ENERGY  EP = F8.3,3HMEV)
 904  FORMAT('   POLARIZATION-PARAMETER FOR VIRTUAL EXCITATION OF THE,
     1    GIANT DIPOLE RESONANCE DIPOLE',F7.4)
 906  FORMAT(52H0SCATTERING ANGLE IN CENTER OF MASS SYSTEM  THETA = F7.2
     1,8H DEGREES)
 908  FORMAT(48H0SCATTERING ANGLE IN LABORATORY SYSTEM  TLBDG = F7.2,
     1 8H DEGREES)
 910  FORMAT(28H0TARGET CHARGE NUMBER  ZT = F6.2,14H,  MASS  A2 = F8.3,
     13HAMU/)
 912  FORMAT(27H0NUMBER OF GROUPS   NGMAX =I3)
 914  FORMAT(///16H0ENERGY SPECTRUM)
 916  FORMAT(//3X,5HGROUPI3,9X,13HLEVEL INDEX N,11I8,/40X,11I8)
 918  FORMAT(1H0,20X,13HENERGY IN MEV,11F8.4,/(40X,11F8.4))
 920  FORMAT(1H0,20X,4HSPIN,11X,11(F5.1,3X),/(40X,11(F5.1,3X)))
 922  FORMAT(1H0,20X,6HPARITY,5X,11I8)
 924  FORMAT(////16H0MASTER - MATRIX)
 926  FORMAT(7X,10I10)
 928  FORMAT(4H0N =I3,10I10)
 930  FORMAT(///26H0MULTIPOLE MATRIX ELEMENTS)
 932  FORMAT(/11H0MATRIX  MEI1,5H(N,M))
 934  FORMAT(///)
 936  FORMAT(6X,I14,10I11)
 938  FORMAT(1H05X3HN =I2,11F11.4)
 940  FORMAT('0PERFORMANCE CONTROLS  NMAX,   INTERV,   NCM,   XIMAX, 
     1   ACCUR,     NTIME')
 942  FORMAT(1H0,19X,I6,2X,2I8,F9.2,F13.7,I9)
 944  FORMAT(12H0GROUP NO. I,10(6X,I2,2X))
 946  FORMAT(9H EMMAX(I),3X,10(5X,F5.1))
 948  FORMAT(10H IEXCIT(I),2X,10(6X,I2,2X))
 950  FORMAT(73H0OUTPUT CONTROLS       OUXI, OUPSI, OUAMP, OUPROW, OURHO
     1B, OURHOC, OURHOX)
 952  FORMAT(1H0,17X3I7,4I8)
 954  FORMAT(69H0TOTAL CROSS SECTIONS FROM CENTER OF MASS DIFFERENTIAL C
     1ROSS SECTIONS)
 956  FORMAT(49H0TOTAL LABORATORY CROSS SECTIONS BETWEEN TLBDG = F7.2,
     120H DEGREES AND TLBDG = F7.2,8H DEGREES )
 958  FORMAT(69H0ERROR - ILLEGAL DEFINITION OF TLBDG AND THETA - EXECUTI
     1ON TERMINATED)
 960  FORMAT(36H   MEM(N,M,LAM) IN  E*BARN**(LAM/2),
     144H  MM(N,M,LAM) IN  MAGNETON*BARN**((LAM-1)/2))
 962  FORMAT(/11H0MATRIX  MMI1,5H(N,M))
 964  FORMAT(1H05X3HN =I2,11E11.3)
 966  FORMAT(38H STEP WIDTH FOR INTEGRATION  DTHETA = F6.2,8H DEGREES)
      END
      SUBROUTINE TENS1
!
!     THIS ROUTINE COMPUTES THE STATISTICAL TENSORS CHARACTERIZING
!     THE ANGULAR DISTRIBUTION OF THE DECAY GAMMA-RAYS
!
      COMPLEX AMP,TE,CI,R
      COMPLEX RHOB,RHOC
      INTEGER OURHOB,OURHOC,OURHOX
      INTEGER SSTART,SSTOP
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL18/CAT(600,3),ICATMX, ISMAX
      COMMON/BL22/THETA
      COMMON/BL23/IDN17,IDN18,IDN19,IDN25
      COMMON/BL24/AMP(600,4)
      COMMON/BL29/RHOB(25,3,5),RHOC(25,3,5)
      COMMON/BL31/OURHOB,OURHOC,OURHOX
      COMMON/BL32/NMAX,NDIM
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL37/TGAMMA,PGAMMA
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL40/SSTART(31),SSTOP(30)
      COMMON/BL42/TCMDG(25),ZLBDG(25),R3(25),R4(25),EPP(25),
     1ETP(25)
      COMMON/BL47/WDCP,WDCT
      COMMON/BL50/OUXI,OUPSI,NCM,EMMAX1
      DATA CI/(0.0,1.0)/
!
!     CALCULATION OF THE STATISTICAL TENSORS RHOB(N,KA,KAPPA) IN COORDIN
!     SYSTEM B
      DO 190 K=1,IEXNUM
      N1 = 2
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IF(K.EQ.1)GOTO 100
      N1 = NSTART(IP) + 1
      N2 = NMAX
 100  LLMAX = 2.0*(SPIN(N1-1)+1.0)
      CE3 = 1.0/(2.0*SPIN(N1-1)+1.0)
      DO 180 N=N1,N2
      CE2 = SQRT(2.0*SPIN(N)+1.0)
      KAMAX = 2.02*SPIN(N)
      IF(KAMAX.GT.4) KAMAX=4
      KASTOP = KAMAX + 1
      KA = 0
      DO 170 KAI=1,KASTOP,2
!     KAI IS INDEX COUNTER ONLY
      KAPSTP = KA + 1
!     CALCULATION OF RHOB FOR KAPPA = K,K-1,......,0
      KAPPA = KA
      DO 160 KAPPI=1,KAPSTP
!     KAPPI IS INDEX COUNTER ONLY
      TE = (0.0,0.0)
      IR1 = SSTART(N)
      IR2 = SSTOP(N)
      DO 150 IR=IR1,IR2
      IRP = IR - KAPPA
      IF(IRP.LT.SSTART(N))GOTO 150
!     DEFINITION OF THE ARGUMENTS OF THE THREE-J SYMBOL
      AA1 = SPIN(N)
      BB1 = -CAT(IR,3)
      BB2 = CAT(IRP,3)
      AA3 = KA
      BB3 = KAPPA
      IEX = SPIN(N) + CAT(IR,3) + 0.01
      FAC = (-1)**IEX * THREEJ(AA1,BB1,AA1,BB2,AA3,BB3)
!     SUMMATION OVER THE MAGNETIC SUBSTATES OF THE GROUND STATE
      L = 1
 110  LL = L + L
      LLL = LLMAX - LL
      IF (LLL) 150,130,120
!     STATEMENT 120 STARTS SUMMATION FOR NEGATIVE QUANTUM NUMBERS
 120  TE = TE + FAC * CONJG(AMP(IR,L)) * AMP(IRP,L)
!     STATEMENT 130 COMPLETES SUMMATION FOR MAGNETIC QUANTUM NUMBERS .GE
 130  JR = 2.02*CAT(IR,3)
      JRP = 2.02*CAT(IRP,3)
      IRPOS = IR - JR
      IRPPOS = IRP - JRP
      TE = TE + FAC * CONJG(AMP(IRPOS,L)) * AMP(IRPPOS,L)
      L = L + 1
      GOTO 110
 150  CONTINUE
      KAINDX = KA/2 + 1
      KAPPIN = KAPPA + 1
      RHOB(N,KAINDX,KAPPIN) = CE2*CE3*TE
      KAPPA = KAPPA - 1
 160  CONTINUE
      KA = KA + 2
 170  CONTINUE
 180  CONTINUE
 190  CONTINUE
      IF(OURHOC.EQ.0)GOTO 490
!
!     CALCULATION OF THE STATISTICAL TENSORS RHOC(N,KA,KAPPA) IN COORDIN
!     SYSTEM C
      DFARG = (180.0 + THETA)/2.0
      DO 480 K=1,IEXNUM
      N1 = 2
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IEXC=IEXCIT(1)
      IF(K.EQ.1)GOTO 300
      N1 = NSTART(IP) + 1
      N2 = NMAX
      IEXC=IEXCIT(IP)
 300  DO 470 N=N1,N2
      KA = 0
      KAMAX = 2.02*SPIN(N)
      IF(KAMAX.GT.4) KAMAX=4
      KASTOP = KAMAX + 1
      DO 460 KAI=1,KASTOP,2
!     KAI IS INDEX COUNTER ONLY
      DJ = KA
      KAINDX = KA/2 + 1
      KAPPA = KA
      KAPSTP = KA + 1
      DO 450 KAPPI=1,KAPSTP
!     KAPPI IS INDEX COUNTER ONLY
      DMP = KAPPA
      KAPPIN = KAPPA + 1
      SUM = (0.,0.)
!     SUMMATION OVER INDICES .GE. 0  IN EQUATION (I.4.9)
      KPR = 0
 390  DM = KPR
      KPRI = KPR + 1
      SUM=SUM+CI**(-KPR)*RHOB(N,KAINDX,KPRI)*DJMM(DFARG,DJ,DM,DMP)
!	dfarg=90.
!	write(55,501)DFARG,DJ,DM,DMP,DJMM(DFARG,DJ,DM,DMP)
!501	format(' ',4f12.4,' ',g13.6)

      KPR = KPR + 1
      IF(KPR.LE.KA)GOTO 390
      IF(KA.EQ.0)GOTO 420
!     SUMMATION OVER NEGATIVE INDICES IN EQUATION (I.4.9)
      KPR = 1
 410  DM = -KPR
      KPRI = KPR + 1
      SUM=SUM+(-1)**KPR*CI**KPR*CONJG(RHOB(N,KAINDX,KPRI))*
     1DJMM(DFARG,DJ,DM,DMP)
!	write(55,501)DFARG,DJ,DM,DMP,DJMM(DFARG,DJ,DM,DMP)


      KPR = KPR + 1
      IF(KPR.LE.KA)GOTO 410
 420  RHOC(N,KAINDX,KAPPIN) = (-1)**KAPPA * SUM
      KAPPA = KAPPA - 1
 450  CONTINUE
      KA = KA + 2
 460  CONTINUE
 470  CONTINUE
 480  CONTINUE
 490  RETURN
      END
      SUBROUTINE TENS2(I)
!
!     THIS ROUTINE PRINTS THE STATISTICAL TENSORS AND COMPUTES TOTAL
!     STATISTICAL TENSORS
!
      COMPLEX RHOB,RHOC,RHOX,RHOXT,RHOCT
      COMMON /BL2/NGMAX,NSTART(10),NSTOP(10),MASTER(10,10),EMMAX(10)
      COMMON /BL3/EN(25),SPIN(25),ACCUR,DIPOL,ZPOL,BANDK(25)
      COMMON /BL9/IEXCIT(10),IEXNUM,LMAX(2),IRSTA(2),IRSTO(2),IP
      COMMON/BL22/THETA
      COMMON/BL29/RHOB(25,3,5),RHOC(25,3,5)
      COMMON/BL30/RHOCT(25,3,5)
      COMMON/BL32/NMAX,NDIM
      COMMON/BL34/SIMP
      COMMON/BL35/ZP,ZT,A1,A2,EP,TLBDG
      COMMON/BL38/ALPHA,BETA,GAMMA
      COMMON/BL42/TCMDG(25),ZLBDG(25),R3(25),R4(25),EPP(25),
     1ETP(25)
      COMMON/BL45/DTHETR,DTLBR
      COMMON/BL46/DSIG(25),DSIGLB(25),RU(25)
      COMMON/BL47/WDCP,WDCT
      COMMON/BL51/SIGTOT(25)
	common/output/iop
      DIMENSION RHOX(25,3,5),RHOXT(25,3,5)
	COMMON/OPT/IOPT  !!
!
      IF(I.EQ.5) CALL ROTATE(RHOX,RHOC,ALPHA,BETA,GAMMA)
      IF(I.EQ.12) CALL ROTATE(RHOXT,RHOCT,ALPHA,BETA,GAMMA)
      DO 540 K=1,IEXNUM
      N1 = 2
      N2 = NMAX
      IF(IEXNUM.EQ.2) N2=NSTART(IP)-1
      IEXC = IEXCIT(1)
      IF(K.EQ.1)GOTO 80
      N1 = NSTART(IP) + 1
      N2 = NMAX
      IEXC = IEXCIT(IP)
  80  IF(I.EQ.3.OR.I.EQ.6.OR.I.EQ.8.OR.I.EQ.9)GOTO 150
      IF(IEXC.EQ.1)GOTO 85
      if(iop.eq.1)write(50,900)
      GOTO 90
  85  if(iop.eq.1)write(50,902)
  90  GOTO(100,103,150,104,105,150,150,150,150,150,150,109,150),I
 100  if(iop.eq.1)write(50,904)
      GOTO 150
 103  if(iop.eq.1)write(50,910)
      GOTO 150
 104  if(iop.eq.1)write(50,912)
      GOTO 150
 105  if(iop.eq.1)write(50,914)
      GOTO 150
 109  if(iop.eq.1)write(50,913)
 150  CONTINUE
      DO 530 N=N1,N2
      KA = 0
      KAMAX = 2.02*SPIN(N)
      IF(KAMAX.GT.4) KAMAX=4
      KASTOP = KAMAX + 1
      DO 520 KAI=1,KASTOP,2
!     KAI IS INDEX COUNTER ONLY
      KAINDX = KA/2 + 1
      KAPSTP = KA + 1
      KAPPA = KA
      DO 510 KAPPI=1,KAPSTP
!     KAPPI IS INDEX COUNTER ONLY
      KAPPIN = KAPPA + 1
      GOTO (200,203,204,205,206,207,208,208,208,208,208,213,208),I
 200  if(iop.eq.1)write(50,920) N,KA,KAPPA,RHOB(N,KAINDX,KAPPIN)
      GOTO 500
 203  RHO = REAL(RHOC(N,KAINDX,KAPPIN))
      if(iop.eq.1)write(50,920) N,KA,KAPPA,RHO  !! TOO MUCH PRINT-OUT
      GOTO 500
 204  CONTINUE
      IF(KAPPA.NE.0) GO TO 500
      RHOCT(N,KAINDX,KAPPIN) = RHOCT(N,KAINDX,KAPPIN) + DTHETR/3.0*
     1SIMP*RHOC(N,KAINDX,KAPPIN)*RU(N)*SIN(THETA/57.295779)*2.*3.1415926
      GOTO 500
 205  RHO = REAL(RHOCT(N,KAINDX,KAPPIN))
      if(iop.eq.1)write(50,920) N,KA,KAPPA,RHO !!TOO MUCH 
      GOTO 500
 206  if(iop.eq.1)write(50,920) N,KA,KAPPA,RHOX(N,KAINDX,KAPPIN)
      GOTO 500
 207  CONTINUE
      IF(KAPPA.NE.0) GO TO 500  !! RESTORED
      RHOCT(N,KAINDX,KAPPIN)=RHOCT(N,KAINDX,KAPPIN)+DTLBR/3.*SIMP*RHOC
     1(N,KAINDX,KAPPIN)*RU(N)*R3(N)*SIN(TLBDG/57.295779)*2.*3.1415926 !! RESTD


!C     1(N,KAINDX,KAPPIN)*RU(N)*R3(N)*SIN(TLBDG/57.295779)*2.*
!C     1 PHI_INT(TLBDG,KAPPA)

!C!!
!C!!	COMPUTES AVERAGE RECOIL DISTANCE AND ENERGY
!C!!
!C	IF(KAINDX.EQ.1.AND.KAPPIN.EQ.1) THEN              !!
!C	  X_NOR=REAL(RHOCT(N,1,1))                        !!
!C	  DIS_AV=DIS_AV+X_NOR/(COS(ZLBDG(N)/57.295779))   !!
!C	  DIS_NOR=DIS_NOR+X_NOR                           !!
!C	  ER_AV=ER_AV+ETP(N)*X_NOR                        !!
!C	ENDIF                                             !!
!C!!

      GOTO 500
 208  CONTINUE
      GOTO 500
 213  if(iop.eq.1)write(50,920) N,KA,KAPPA,RHOXT(N,KAINDX,KAPPIN)
      GOTO 500
 500  KAPPA = KAPPA - 1
 510  CONTINUE
      KA = KA + 2
 520  CONTINUE
	if(iop.eq.1)then
      IF(I.NE.3.AND.I.NE.6.AND.I.NE.8.AND.I.NE.9)write(50,916)
	endif
!
	IF(I.EQ.4)THEN						!!
	  WRITE(8,*)N						!!
	  DO KR=1,3						!!
	    KR2=2*KR-1						!!
	    WRITE(8,'(5E12.4)')
     1	    (REAL(RHOCT(N,KR,KR1)),KR1=1,KR2)			!!
	  ENDDO							!!
	  IF(N.EQ.NMAX)THEN					!!
	    WRITE(8,'(2E12.4)')DIS_AV/DIS_NOR,ER_AV/DIS_NOR	!!
	    DIS_AV=0.						!!
	    DIS_NOR=0.						!!
	    ER_AV=0.						!!
	  ENDIF							!!
	ENDIF							!!
!
 530  CONTINUE
 540  CONTINUE
      RETURN
 900  FORMAT(27H0TENSORS FOR TARGET NUCLEUS)
 902  FORMAT(31H0TENSORS FOR PROJECTILE NUCLEUS)
 904  FORMAT(7X1HN5X2HKA4X5HKAPPA9X9HREAL RHOB13X9HIMAG RHOB)
 910  FORMAT(7X,1HN5X2HKA4X5HKAPPA9X9HREAL RHOC)
 912  FORMAT(7X1HN5X2HKA4X5HKAPPA9X10HREAL RHOCT/)
 913  FORMAT(7X1HN5X2HKA4X5HKAPPA9X10HREAL RHOXT11X10HIMAG RHOXT/)
 914  FORMAT(7X,1HN5X2HKA4X5HKAPPA9X9HREAL RHOX13X9HIMAG RHOX)
 916  FORMAT(1H0)
 920  FORMAT(1H 3I7,2E22.4)
      END
      FUNCTION THREEJ(RJ1,RM1,RJ2,RM2,RJ3,RM3)
!
!     THIS ROUTINE COMPUTES THE THREE-J-SYMBOL ACCORDING TO EQ. (II.23.1
!
      COMMON /BL8/ASQRT,B(200),IEX(200)
      J1=2.001*RJ1
      J2=2.001*RJ2
      J =2.001*RJ3
      M1=2.001*RM1
      M2=2.001*RM2
      M =2.001*RM3
      SUM=0.0
      IF((M1+M2+M.NE.0).OR.(J.GT.J1+J2).OR.(J.LT.IABS(J1-J2))) GOTO 400
      IF((IABS(M1).GT.J1).OR.(IABS(M2).GT.J2).OR.(IABS(M).GT.J))GOTO 400
      K2MIN=0
      IF(J-J2+M1.LT.0) K2MIN=-J+J2-M1
      IF(J-J1-M2+K2MIN.LT.0) K2MIN=-J+J1+M2
      K2MAX=J1+J2-J
      IF(J2+M2-K2MAX.LT.0) K2MAX=J2+M2
      IF(J1-M1-K2MAX.LT.0) K2MAX=J1-M1
      JA=(J1+M1)/2+1
      JB=JA-M1
      JC=(J2+M2)/2+1
      JD=JC-M2
      JE=(J +M )/2+1
      JF=JE-M
      JG=(J1+J2-J)/2+1
      JH=JA+JB-JG
      JI=JC+JD-JG
      JJ=JE+JF+JG-1
      IF (JJ .GT. 200) GOTO 600
!     STATEMENT 600 STOPS THE COMPUTATION IF THE RANGE OF FACTORIALS IS
      B1=B(JA)*B(JB)*B(JC)*B(JD)*B(JE)*B(JF)*B(JG)*B(JH)*B(JI)/B(JJ)
      IEX1=IEX(JA)+IEX(JB)+IEX(JC)+IEX(JD)+IEX(JE)+IEX(JF)+IEX(JG)+
     1IEX(JH)+IEX(JI)-IEX(JJ)
      IA=K2MIN/2
      IB=JG-IA+1
      IC=JB-IA+1
      ID=JC-IA+1
      IE=JA-JG+IA
      IF=JD-JG+IA
      FASE=1.0
      IF(MOD(IA,2).EQ.0) FASE=-FASE
      K2 =K2MIN
!
!     SUMMATION OVER K STARTS HERE
 100  IA=IA+1
      IB=IB-1
      IC=IC-1
      ID=ID-1
      IE=IE+1
      IF=IF+1
      FASE=-FASE
      B2=B(IA)*B(IB)*B(IC)*B(ID)*B(IE)*B(IF)
      IEX2=IEX(IA)+IEX(IB)+IEX(IC)+IEX(ID)+IEX(IE)+IEX(IF)
      STOR=SQRT(B1/(B2*B2) * 10.0**(IEX1-IEX2-IEX2))
      SUM = SUM + FASE*STOR
      K2=K2+2
      IF(K2.LE.K2MAX) GOTO 100
      N = ABS(RJ1-RJ2-RM3)+0.01
      SUM = (-1)**N * SUM
 400  THREEJ=SUM/ASQRT
      RETURN
!
!     ERROR EXIT
 600  write(50,902)
      write(50,904)RJ1,RJ2,RJ3,RM1,RM2,RM3
      STOP
!
 902  FORMAT(29H0 ERROR - FACTORIALS EXCEEDED)
 904  FORMAT(6H0RJ1 =F6.2,6H RJ2 =F6.2,6H RJ3 =F6.2,6H RM1 =F6.2,
     16H RM2 =F6.2,6H RM3 =F6.2)
      END
      SUBROUTINE ZCLOCK(T)
!
!     THIS ROUTINE CALLS AN INTERNAL TIME ROUTINE SPECIFIC TO
!     THE USED COMPUTER. FOR OTHER COMPUTERS CHANGE OR REPLACE
!     THE TIME ROUTINE
!
!     CALL SECOND(T)
      RETURN
      END
