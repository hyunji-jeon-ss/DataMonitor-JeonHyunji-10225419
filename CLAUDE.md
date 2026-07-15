# CLAUDE.md — DataMonitor-JeonHyunji-10225419

## 프로젝트 개요
데이터 모니터링 Tool PoC. `DataPersistence` PoC에서 검증한 저장소 구조를 참조하여, 저장된 데이터 상태를 콘솔에서 조회하는 관리자 도구를 구현한다.

## 기술 스택 / 컨벤션
- C++20, Visual Studio(MSBuild, .vcxproj), gmock(NuGet)
- 코드 컨벤션은 상위 `Semiconductor` 폴더의 `CODE_CONVENTION.md`를 따른다.

## 설계 방향
- 조회 전용(read-only) 클라이언트로 구현, 저장소를 직접 변경하지 않는다.
- 외부에서 데이터가 변경된 뒤 재조회 시 최신 상태가 반영되는지를 핵심으로 검증한다.
- **검색 기능**: 이름/ID 등 속성 기준으로 조건에 맞는 데이터만 필터링하여 조회할 수 있어야 한다.

## 테스트
- 저장소 인터페이스를 gmock으로 목킹하여 조회 로직을 단위 테스트한다.
- 검색 조건 매칭/불일치, 빈 결과 등 검색 로직의 경계 케이스를 단위 테스트로 검증한다.

## 한글 인코딩 (중요)
콘솔에 한글을 출력하므로 반드시 아래 두 가지를 유지한다. 자세한 이유는 상위 `Semiconductor` 폴더의 `CLAUDE.md` 참고.
1. 모든 `.vcxproj`의 각 ClCompile 설정에 `<AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>` 적용
2. 콘솔 진입점(main)에서 `SetConsoleOutputCP(CP_UTF8)` / `SetConsoleCP(CP_UTF8)` 호출

## 커밋 컨벤션
`COMMIT_CONVENTION.md`를 따른다. 커밋 메시지는 `<헤더> 변경 내용` 형식이며, 헤더는 `<FEATURE>`/`<FIX>`/`<DOCS>`/`<STYLE>`/`<REFACTOR>`/`<TEST>`/`<CHORE>` 중 하나만 사용한다.

## 빌드/실행
Visual Studio에서 솔루션을 열어 빌드/실행한다.
