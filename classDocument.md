# 기능 목록

## 튜링 머신 구현하기

- 테이블 구현
  - 용량의 관계 없이 규칙 추가가 가능한 테이블 캡슐화하여 구현하기

- 테이프 구현하기
	- 튜링머신은 테이프에 작성된 값을 통해 계산을 진행함
	- 좌우로 무한히 확장 가능한 테이프 캡슐화하여 구현하기

- 튜링머신 구현하기
	- 규칙 테이블에 따라 값을 업데이트하는 튜링머신 캡슐화하여 구현

	--------------------------------------------------------------------------------------

## 함수 목록 확인

- main.cpp
	- 튜링머신 함수 호출을 위한 함수

- test_[table/tape/machine].cpp

  - 3가지 구현기능 정상 동작 확인 함수

- util.[h/cpp]
	- 과제 도움 함수

- TuringMachine.[h/cpp]
	- 실제 과제 구현 함수
	- table, tape, machine class 구현할 것

	------------------------------------------------

	## Table

- addTransition
	+ [0] 테이블에 규칙을 추가하는 기능

- print 
	+ [0] 형식에 맞춰 모든 table 출력
	+ [] transition print에 반복 추가하면 될 것으로 보임

- clear
	+ [0] 테이블 내 모든 규칙 제거
	
- findTransition
	+ [0] rule에 맞는 table 값이 있다면 transition print 통해 출력
	+ [0] 와일드 카드 사용시 임의 문자로 해석하고 여러 테이블 출력 가능하면 상단 테이블 출력할 것
	+ [0] 와일드 카드 미사용 입력 시 테이블에 존재하지 않으면 와일드카드로 대응 가능

- initialize
	+ [0] 기존 테이블 제거
	+ [0] 줄단위로 문자열 읽고 각 테이블에 적용
	+ [0] util class 활용가능

- load
	+ [0] initialize 기능을 txt 파일 열어서 실행




- private
	+ [0] 규칙의 type이 각자 다름, 하나의 vector element로 구성할 수 있는가?
	+ [0] 규칙입력 class인 transition 자체를 type으로 하는 vector transitionTable 구성
	
	+ [0] string을 입력받아 변환 후 addTransition을 진행하는 stringToTable 함수
	+ [0] load에서 addTransition의 반복 사용 필요
	

	---------------------------------------------------
	## Tape
	+ [0] vector의 기본 구조처럼 구현 (double이 아닌 char로 구현)
	
	+ [0] vector 구조에서 [0] 위치에 문자 값 추가하는 push_front함수 구현_
	+ [0] 문자열 입력시 해당 크기로 벡터 객체 생성하는 initialize 함수 구현
	+ [0] 모든 element 출력하는 print 함수 구현




	-------------------------------------------------

	## Machine