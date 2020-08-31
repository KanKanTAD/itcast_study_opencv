#!/usr/bin/env python
# -*- coding:utf-8 -*-

import gym
import numpy as np
import random
import tensorflow as tf
import numpy as np
import sys
import time
from tensorflow.keras import Sequential, layers
from tensorflow.keras import optimizers, losses, activations, metrics


class dqn_agent:

    def __init__(self, env):
        self.env = env

        self.gamma = 0.92
        self.clear_remember()
        self._build_model()

    def _build_model(self, file_name=None):
        if file_name is not None:
            self.model = tf.ketf.keras.models.load_model(file_name)
            return

        self.model = Sequential([
            layers.Flatten(input_shape=[2, 128, 1]),
            layers.Dense(128 * 4, activation=activations.relu),
            layers.Dense(72, activation=activations.relu),
            layers.Dense(self.env.action_space.n,
                         activation=activations.softmax)
        ])
        self.model.compile(optimizer=optimizers.SGD(),
                           loss=losses.MSE,
                           metrics=['accuracy'])

    def _normal(self, arr):
        return np.asarray(arr).reshape((128, 1)) / 255.0

    def clear_remember(self):
        self.memory = []

    def get_action(self, observation, prev_observation=None):
        if prev_observation is None:
            return self.random_action()
        else:
            return self.predict(observation, prev_observation)

    def __predict(self, observation, prev_observation):
        delta_observation = observation - prev_observation
        ob = np.asarray([self._normal(observation), self._normal(
            delta_observation)]).reshape((1, 2, 128, 1))
        pred = self.model.predict(ob)
        return pred[0, :]

    def predict(self, observation, prev_observation):
        q_arr = self.__predict(observation, prev_observation)
        act = np.random.choice(len(q_arr), 1, p=q_arr, replace=False)
        return act[0]

    def random_action(self):
        return self.env.action_space.sample()

    def learn_step(self, prev_observation, observation,
                   action, reward, next_observation):
        x = np.asarray([observation, observation - prev_observation]
                       ).reshape((1, 2, 128, 1)) / 255.0
        x_prime = np.asarray([next_observation, next_observation-observation]
                             ).reshape((1, 2, 128, 1)) / 255.0
        q_pred = np.amax(self.model.predict(x_prime)[0, :])
        q_target = reward + self.gamma * q_pred
        q_table_now = self.model.predict(x)[0, :]
        q_table_now[action] = q_target
        y = np.asarray([q_table_now])

        history = self.model.fit(x, y, epochs=1)
        return

    def save_model(self, name='0xfff.h5'):
        self.model.save(name)


def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


def half_sigmoid(z, beta=1.0):
    return z / (beta + z)


def train(max_episode=200, file_name='0x004.1.h5'):
    env = gym.make("Breakout-ram-v4")
    agent = dqn_agent(env)

    is_render = True

    alpha = 1.0
    total_reward = 0
    total_error = 0
    best_rewards = -9999999

    for episode in range(max_episode):

        prev_observation = None
        observation = env.reset()
        if is_render:
            env.render()
        done = False
        step_counter = 0

        main_lives = 5

        while not done:
            step_counter += 1
            action = agent.get_action(observation, prev_observation)
            next_observation, reward, done, info = env.step(action)

            if info["ale.lives"] < main_lives:
                main_lives = info["ale.lives"]
                reward = -0.444

            total_reward += reward
            reward *= alpha

            if prev_observation is not None:
                agent.learn_step(prev_observation, observation,
                                 action, reward, next_observation)

            prev_observation = observation
            observation = next_observation
            if is_render:
                env.render()
            if done:
                print("Episode:{},step:{}".format(episode, step_counter))

                error = total_reward - best_rewards
                if error > 0:
                    best_rewards = total_reward
                    alpha = 1.0
                    total_error = 0
                else:
                    total_error += abs(error)
                    alpha = 1.0 + 2*3.1415 * half_sigmoid(total_error, 6*8)
                print("best_rewards:{},total_reward:{},total_error:{},alpha:{}".format(
                    best_rewards, total_reward, total_error, alpha))
                total_reward = 0
                break

    agent.save_model(name=file_name)
    time.sleep(1)
    env.close()


def get_action(model, observation, prev_observation=None):
    if prev_observation is None or (random.random() > 0.973):
        return random.randint(0, 3)
    ob = np.asarray([observation, prev_observation]
                    ).reshape((1, 2, 128, 1)) / 255.0
    act = np.argmax(model.predict(ob)[0, :])
    return act


def test(file_name='0x004.1.h5'):
    env = gym.make("Breakout-ram-v4")
    model = tf.keras.models.load_model(file_name)

    max_episode = 3

    for episode in range(max_episode):
        prev_observation = None
        observation = env.reset()
        env.render()
        done = False
        step_counter = 0
        while not done:
            step_counter += 1
            action = get_action(model, observation, prev_observation)
            prev_observation = observation
            observation, reward, done, info = env.step(action)

            env.render()
            if done:
                print("Episode:{},reward:{},step:{}".format(
                    episode, reward, step_counter))
                break

    time.sleep(1)
    env.close()


if __name__ == '__main__':
    train(max_episode=500)
    test()
