# DataMonitor-JeonHyunji-10225419

반도체 시료 생산주문관리 시스템 개인과제 — **[미션1] PoC: 데이터 모니터링 Tool**

## 목적
현재 저장된 데이터 상태를 콘솔에서 실시간으로 조회할 수 있는 관리자 도구를 검증하는 PoC.
전체 목록 조회뿐 아니라, 특정 속성(이름, ID 등)으로 데이터를 검색하는 기능도 포함한다.

## 기술 스택
- C++20, Visual Studio (MSBuild, .vcxproj)
- nlohmann/json (NuGet, `nlohmann.json`) — JSON 파일 읽기
- gmock (NuGet, v1.11.0) 기반 단위 테스트

## 구조
```
DataMonitor.sln
DataMonitorLib/
  model/Item.h
  repository/IItemReader.h            조회 전용 인터페이스 (findAll/findById/searchByName)
  repository/JsonItemReader.h/.cpp    nlohmann/json 기반 구현체 (읽기만 수행, 파일 미변경)
DataMonitorApp/     # 콘솔 뷰어 (main.cpp), Lib 참조
DataMonitorTest/    # gmock 기반 단위 테스트, Lib 참조
```
`JsonItemReader`는 매 호출마다 파일을 새로 읽으므로 캐싱이 없다 — 외부에서 `items.json`이 변경된 뒤 다시 조회하면 즉시 최신 상태가 반영된다.

## 빌드 방법 (Visual Studio)
1. `DataMonitor.sln`을 Visual Studio로 연다.
2. NuGet이 자동으로 `nlohmann.json`(3.12.0), `gmock`(1.11.0)을 복원한다 (안 되면 솔루션 우클릭 → NuGet 패키지 복원).
3. 구성을 **Debug / x64**로 맞추고 `Ctrl+Shift+B` 빌드.

## 실행 방법
- **조회 도구**: `DataMonitorApp`을 시작 프로젝트로 설정 후 `Ctrl+F5` 실행
  - 실행 폴더에 `items.json`이 있어야 조회할 내용이 보인다 (`DataPersistence`/`DummyDataGenerator`로 만든 `items.json`을 실행 폴더에 복사해서 테스트 가능)
  - 메뉴: `1`(전체 조회) `2`(이름 검색, 대소문자 무시 부분일치) `3`(id 조회) `0`(종료)
- **테스트**: `DataMonitorTest`를 시작 프로젝트로 설정 후 `Ctrl+F5` 실행

## 관련 문서
- 상위 저장소의 `PRD.md`, `PLAN.md` Phase 3 참고
