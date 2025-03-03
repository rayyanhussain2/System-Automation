from langchain_openai import ChatOpenAI
from browser_use import Agent
import asyncio
import sys
from dotenv import load_dotenv
load_dotenv()

async def main():
    # Read task from stdin
    task = sys.stdin.readline().strip()
    
    agent = Agent(
        task=task,
        llm=ChatOpenAI(model="gpt-4"),
    )
    result = await agent.run()
    print(result)

asyncio.run(main())