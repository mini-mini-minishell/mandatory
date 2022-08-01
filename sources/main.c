#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	check_arguments(argc, argv);  //예외처리 하는곳
	// envp 저장 (list)
	// while (1)
		// readline
		// lexer
		// parsing
	init_parsing(envp);

	// 파싱부 (파싱 테이블 + 트리 구현)
		// lexer : 토큰 나누는 곳
		// parser : 트리에 저장하고 트리를 만듦, 테이블 구현
	// 프롬프트 띄우기
	// 실행부(bulit-in, executable)

	// 환경변수 저장 -> pasing or execute
	return (0);
}

