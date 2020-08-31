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

        self.beta = 0.94
        self.gamma = 0.83
        self.clear_remember()
        self._build_model()

    def _build_model(self, file_name=None):
        if file_name is not None:
            self.model = tf.ketf.keras.models.load_model(file_name)
            return

        self.model = Sequential([
            layers.Flatten(input_shape=[2, 128, 1]),
            layers.Dense(120 * 5, activation=activations.relu),
            layers.Dense(72, activation=activations.relu),
            layers.Dense(24, activation=activations.relu),
            layers.Dense(self.env.action_space.n,
                         activation=activations.softmax)
        ])
        self.model.compile(optimizer=optimizers.SGD(),
                           loss=losses.MSE, metrics=['accuracy'])

    def _normal(self, arr):
        return np.asarray(arr).reshape((128, 1)) / 255.0

    def clear_remember(self):
        self.memory = []

    def remember(self, observation, action, reward, next_observation):
        self.memory.append([self._normal(observation),
                            action,
                            reward,
                            self._normal(next_observation)])

    def q_get_action(self, observation, prev_observation=None):
        if prev_observation is None or (random.random() > 0.91):
            return self.random_action()
        else:
            return self.max_predict(observation, prev_observation)

    def get_action(self, observation, prev_observation=None):
        if prev_observation is None:
            return self.random_action()
        else:
            return self.predict(observation, prev_observation)

    def __predict(self, observation, prev_observation):
        ob = np.asarray([self._normal(observation), self._normal(
            prev_observation)]).reshape((1, 2, 128, 1))
        pred = self.model.predict(ob)
        return pred[0, :]

    def predict(self, observation, prev_observation):
        q_arr = self.__predict(observation, prev_observation)
        act = np.random.choice(len(q_arr), 1, p=q_arr, replace=False)
        return act[0]

    def max_predict(self, observation, prev_observation):
        q_arr = self.__predict(observation, prev_observation)
        return np.argmax(q_arr)

    def random_action(self):
        return self.env.action_space.sample()

    def sample_from_memory(self, batch_size=32):
        if len(self.memory) <= 0:
            return None
        batch_size = min(batch_size, len(self.memory))
        indeies = np.random.choice(
            list(range(len(self.memory))), replace=False, size=batch_size)
        indeies = np.int0(indeies)
        sam = []
        for ix in indeies:
            sam.append(self.memory[ix])
        return sam

    def learn_step(self, observation, action, reward,
                   next_observation, batch_size=32, epochs=2):

        if reward != 0:
            # self.memory = self.sample_from_memory()
            beta = 1.0
            for i in range(len(self.memory)):
                self.memory[i][2] = reward * beta
                beta *= self.beta
            self.learn(epochs=2)

        self.remember(observation, action, reward, next_observation)

    def learn(self, batch_size=32, epochs=8):

        obs = []
        qs = []

        for i in range(1, len(self.memory)):
            prev_ob, _, _, _ = self.memory[i-1]
            ob, act, rew, nxt_ob = self.memory[i]
            x = np.asarray([ob, prev_ob])
            obs.append(x)
            q_pred = np.amax(self.__predict(nxt_ob, ob))
            q_target = rew + self.gamma * q_pred
            q_table_now = self.__predict(ob, prev_ob)
            q_table_now[act] = q_target
            qs.append(q_table_now)

        batch_size = min(batch_size, len(self.memory))

        history = self.model.fit(np.asarray(obs).reshape((-1, 2, 128, 1)),
                                 np.asarray(qs),
                                 epochs=epochs,
                                 verbose=0)
        print('loss:', history.history['loss'])
        self.clear_remember()

    def save_model(self, name='0xfff.h5'):
        self.model.save(name)


def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


def half_sigmoid(z, beta=1.0):
    return z / (beta + z)


def train(max_episode=200, file_name='0x005.1.h5'):
    env = gym.make("Breakout-ram-v4")
    agent = dqn_agent(env)

    is_render = True

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
            # action = agent.q_get_action(observation, prev_observation)
            next_observation, reward, done, info = env.step(action)

            if info["ale.lives"] < main_lives:
                main_lives = info["ale.lives"]
                reward = -0.75

            agent.learn_step(observation, action, reward, next_observation)

            prev_observation = observation
            observation = next_observation

            if is_render:
                env.render()
            if done:
                print("Episode:{},step:{}".format(episode, step_counter))
                break

    agent.save_model(name=file_name)
    time.sleep(1)
    env.close()


def get_action(model, observation, prev_observation=None):
    if prev_observation is None:
        return np.random.randint(0, 3)
    ob = np.asarray([observation, prev_observation]
                    ).reshape((1, 2, 128, 1)) / 255.0
    act = np.argmax(model.predict(ob)[0, :])
    return act


def test(file_name='0x005.1.h5'):
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
