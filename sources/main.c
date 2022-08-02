#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_all_lists	all_lists;

	check_arguments(argc, argv);  //예외처리 하는곳
	init_all(&all_lists, envp);
	// envp 저장 (list)
	// while (1)
		// readline
		// lexer
		// parsing

	// 파싱부 (파싱 테이블 + 트리 구현)
		// lexer : 토큰 나누는 곳
		// parser : 트리에 저장하고 트리를 만듦, 테이블 구현
	// 프롬프트 띄우기
	// 실행부(bulit-in, executable)

	// 환경변수 저장 -> pasing or execute
	return (0);
}

